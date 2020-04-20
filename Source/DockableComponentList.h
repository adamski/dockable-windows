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


/**
A really simple component we can use to test the dragging and docking.
*/
class ExampleDockableComponent
        : public Component
{
public:
    ExampleDockableComponent(const String & componentName, const Colour & colour_)
            :
            colour(colour_)
    {
        Component::setName(componentName);
    }

    ~ExampleDockableComponent()
    {
        jassertfalse;
    }

    void paint(Graphics & g) override
    {
        g.fillAll(colour);
        g.setColour(Colours::white);
        g.drawText("Window Content", getLocalBounds(), Justification::centred, false);
    }

private:
    Colour colour;
};

class DockableComponentList : public ValueTreeObjectList<DockableComponentWrapper>
{
public:
    DockableComponentList(const juce::ValueTree &parentTree, DockableWindowManager &dockableWindowManager)
            : ValueTreeObjectList(parentTree), dockableWindowManager(dockableWindowManager)
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
        return hasValidType(tree);
    }

    bool hasValidType(const juce::ValueTree &tree) const
    {
        return DockableComponentTypes::types.find(tree[Ids::type].toString()) != DockableComponentTypes::types.end();
    }

    DockableComponentWrapper* createNewObject(const juce::ValueTree &tree) override
    {
        jassert(tree.hasType(Ids::Component));
        jassert(tree.hasProperty(Ids::type));
        jassert(hasValidType(tree));

        auto baseColour = Colours::blue.withSaturation(0.4f).withBrightness(0.4f);
        auto randFloat = (rand() % 100) / 100;
        auto info = DockableComponentTypes::types[tree[Ids::type]];

        return new DockableComponentWrapper(dockableWindowManager, new ExampleDockableComponent(info.title, baseColour.withRotatedHue(randFloat)));
    }

    void deleteObject(DockableComponentWrapper* type) override
    {
        //...?
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

    DockableWindowManager& dockableWindowManager;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DockableComponentList)
};
