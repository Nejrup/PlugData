/*
 // Copyright (c) 2015-2022 Pierre Guillot and Timothy Schoen.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "Utility/Config.h"
#include <juce_gui_basics/juce_gui_basics.h>

extern "C" {
#include <s_inter.h>
}

#include "WeakReference.h"
#include "Instance.h"

pd::WeakReference::WeakReference(void* p, Instance* instance)
    : ptr(static_cast<t_pd*>(p))
    , pd(instance)
{
    pd->registerWeakReference(ptr, &weakRef);
}

pd::WeakReference::~WeakReference()
{
    pd->unregisterWeakReference(ptr, &weakRef);
}

void pd::WeakReference::setThis() const
{
    pd->setThis();
}
