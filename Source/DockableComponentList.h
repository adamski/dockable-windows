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
#include "Identifiers.h"

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
        if (! tree.hasType(Ids::Component)) return false;
        if (! tree.hasProperty(Ids::type)) return false;
        return (DockableComponentTypes::types.find(tree[Ids::type].toString()) != DockableComponentTypes::types.end());
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
