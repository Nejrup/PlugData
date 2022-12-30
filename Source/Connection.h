/*
 // Copyright (c) 2021-2022 Timothy Schoen
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#pragma once

#include <JuceHeader.h>

extern "C" {
#include <m_pd.h>
}

#include "Iolet.h"

using PathPlan = std::vector<Point<int>>;

class Canvas;
class Connection : public Component
    , public ComponentListener
    , public Value::Listener {
public:
    int inIdx;
    int outIdx;

    SafePointer<Iolet> inlet, outlet;
    SafePointer<Object> inobj, outobj;

    Path toDraw;
    String lastId;

    Connection(Canvas* parent, Iolet* start, Iolet* end, bool exists = false);
    ~Connection() override;

    void paint(Graphics&) override;

    bool isSegmented();
    void setSegmented(bool segmented);

    void updatePath();

    bool hitTest(int x, int y) override;

    void mouseDown(MouseEvent const& e) override;
    void mouseMove(MouseEvent const& e) override;
    void mouseDrag(MouseEvent const& e) override;
    void mouseUp(MouseEvent const& e) override;
    void mouseExit(MouseEvent const& e) override;

    Point<int> getStartPoint();
    Point<int> getEndPoint();

    void reconnect(Iolet* target, bool dragged);

    bool intersects(Rectangle<float> toCheck, int accuracy = 4) const;
    int getClosestLineIdx(Point<int> const& position, PathPlan const& plan);

    String getId() const;

    String getState();
    void setState(String const& block);

    void componentMovedOrResized(Component& component, bool wasMoved, bool wasResized) override;

    // Pathfinding
    int findLatticePaths(PathPlan& bestPath, PathPlan& pathStack, Point<int> start, Point<int> end, Point<int> increment);

    void findPath();

    bool intersectsObject(Object* object);
    bool straightLineIntersectsObject(Line<int> toCheck, Array<Object*>& objects);

private:
    bool wasSelected = false;
    bool segmented = false;

    Array<SafePointer<Connection>> reconnecting;

    Rectangle<float> startReconnectHandle, endReconnectHandle;

    PathPlan currentPlan;

    Value locked;

    Canvas* cnv;

    Point<int> origin, offset;

    int dragIdx = -1;

    float mouseDownPosition = 0;

    Value useDashedSignalConnection;
    bool useDashed;

    void valueChanged(Value& v) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Connection)
};
