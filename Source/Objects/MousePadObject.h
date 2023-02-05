/*
 // Copyright (c) 2021-2022 Timothy Schoen
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

// ELSE mousepad
class MousePadObject final : public ObjectBase {
    bool isPressed = false;

    Point<int> lastPosition;

    typedef struct _pad {
        t_object x_obj;
        t_glist* x_glist;
        void* x_proxy; // dont have this object and dont need it
        t_symbol* x_bindname;
        int x_x;
        int x_y;
        int x_w;
        int x_h;
        int x_sel;
        int x_zoom;
        int x_edit;
        unsigned char x_color[3];
    } t_pad;

public:
    MousePadObject(void* ptr, Object* object)
        : ObjectBase(ptr, object)
    {
        cnv->addMouseListener(this, true);
    }

    ~MousePadObject()
    {
        cnv->removeMouseListener(this);
    }

    void paint(Graphics& g) override
    {
        auto* x = static_cast<t_pad*>(ptr);
        auto fillColour = Colour(x->x_color[0], x->x_color[1], x->x_color[2]);
        g.setColour(fillColour);
        g.fillRoundedRectangle(getLocalBounds().toFloat().reduced(0.5f), PlugDataLook::objectCornerRadius);

        auto outlineColour = object->findColour(cnv->isSelected(object) && !cnv->isGraph ? PlugDataColour::objectSelectedOutlineColourId : PlugDataColour::outlineColourId);

        g.setColour(outlineColour);
        g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(0.5f), PlugDataLook::objectCornerRadius, 1.0f);
    };

    void mouseDown(MouseEvent const& e) override
    {
        auto relativeEvent = e.getEventRelativeTo(this);

        if (!getLocalBounds().contains(relativeEvent.getPosition()) || !isLocked() || !object->cnv->isShowing() || isPressed)
            return;

        auto* x = static_cast<t_pad*>(ptr);
        t_atom at[3];

        x->x_x = relativeEvent.getPosition().x;
        x->x_y = getHeight() - relativeEvent.getPosition().y;

        SETFLOAT(at, 1.0f);
        sys_lock();
        outlet_anything(x->x_obj.ob_outlet, pd->generateSymbol("click"), 1, at);
        sys_unlock();

        isPressed = true;
    }

    void mouseDrag(MouseEvent const& e) override
    {
        if ((!getScreenBounds().contains(e.getMouseDownScreenPosition()) && !isPressed) || !isLocked())
            return;

        auto* x = static_cast<t_pad*>(ptr);
        t_atom at[3];

        auto relativeEvent = e.getEventRelativeTo(this);

        // Don't repeat values
        if (relativeEvent.getPosition() == lastPosition)
            return;

        x->x_x = relativeEvent.getPosition().x;
        x->x_y = getHeight() - relativeEvent.getPosition().y;

        SETFLOAT(at, x->x_x);
        SETFLOAT(at + 1, x->x_y);

        lastPosition = { x->x_x, getHeight() - x->x_y };

        sys_lock();
        outlet_anything(x->x_obj.ob_outlet, &s_list, 2, at);
        sys_unlock();
    }

    void mouseMove(MouseEvent const& e) override
    {
        if (!getScreenBounds().contains(e.getScreenPosition()) || isPressed || !isLocked())
            return;

        auto* x = static_cast<t_pad*>(ptr);
        t_atom at[3];

        auto relativeEvent = e.getEventRelativeTo(this);

        // Don't repeat values
        if (relativeEvent.getPosition() == lastPosition)
            return;

        x->x_x = relativeEvent.getPosition().x;
        x->x_y = getHeight() - relativeEvent.getPosition().y;

        SETFLOAT(at, x->x_x);
        SETFLOAT(at + 1, x->x_y);

        lastPosition = { x->x_x, getHeight() - x->x_y };

        sys_lock();
        outlet_anything(x->x_obj.ob_outlet, &s_list, 2, at);
        sys_unlock();
    }

    void mouseUp(MouseEvent const& e) override
    {
        if ((!getScreenBounds().contains(e.getMouseDownScreenPosition()) || !isPressed) || !isLocked())
            return;

        auto* x = static_cast<t_pad*>(ptr);
        t_atom at[1];
        SETFLOAT(at, 0);
        outlet_anything(x->x_obj.ob_outlet, pd->generateSymbol("click"), 1, at);
        isPressed = false;
    }

    void applyBounds() override
    {
        auto b = object->getObjectBounds();
        libpd_moveobj(cnv->patch.getPointer(), static_cast<t_gobj*>(ptr), b.getX(), b.getY());

        auto* pad = static_cast<t_pad*>(ptr);
        pad->x_w = b.getWidth();
        pad->x_h = b.getHeight();
    }

    void updateBounds() override
    {
        pd->getCallbackLock()->enter();

        int x = 0, y = 0, w = 0, h = 0;
        libpd_get_object_bounds(cnv->patch.getPointer(), ptr, &x, &y, &w, &h);

        pd->getCallbackLock()->exit();

        object->setObjectBounds({ x, y, w, h });
    }

    // Check if top-level canvas is locked to determine if we should respond to mouse events
    bool isLocked()
    {

        // Find top-level canvas
        auto* topLevel = findParentComponentOfClass<Canvas>();
        while (auto* nextCanvas = topLevel->findParentComponentOfClass<Canvas>()) {
            topLevel = nextCanvas;
        }

        return static_cast<bool>(topLevel->locked.getValue());
    }

    void receiveObjectMessage(String const& symbol, std::vector<pd::Atom>& atoms) override
    {
        switch (hash(symbol.toUTF8())) {
        case objectMessage::msg_color: {
            repaint();
            break;
        }
        default:
            break;
        }
    }
};
