/*
  ==============================================================================

    DockableComponentList.h
    Created: 17 Apr 2020 11:25:12am
    Author:  Adam Wilson

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "ValueTreeObjectList.h"
#include "JDockableWindows.h"

class DockableComponentList : public ValueTreeObjectList<DockableComponentWrapper>
{
public:
    DockableComponentList(const juce::ValueTree &parentTree) : ValueTreeObjectList(parentTree)
    {
        rebuildObjects();
    }


    ~DockableComponentList() override
    {
        freeObjects();
    }

    bool isSuitableType(const juce::ValueTree &tree) const override
    {
        return false;
    }

    DockableComponentWrapper* createNewObject(const juce::ValueTree &tree) override
    {
        return nullptr;
    }

    void deleteObject(DockableComponentWrapper* type) override
    {

    }

    void newObjectAdded(DockableComponentWrapper* type) override
    {

    }

    void objectRemoved(DockableComponentWrapper* type) override
    {

    }

    void objectOrderChanged() override
    {

    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DockableComponentList)
};
