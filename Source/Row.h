/*
  ==============================================================================

    RowList.h
    Created: 20 Apr 2020 11:31:52am
    Author:  Adam Wilson

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "ValueTreeObjectList.h"
#include "JDockableWindows.h"
#include "Identifiers.h"
#include "Column.h"

/**
Manages a row of windows complete with vertical resizer bars.
*/
class RowType
{
public:
    RowType(ValueTree& layoutTree) : layoutTree(layoutTree)
    {
        layout = std::make_unique<StretchableLayoutManager>();
    }

    RowType(RowType &&rhs) : layoutTree(rhs.layoutTree)
    {
        resizers = std::move(rhs.resizers);
        layout = std::move(rhs.layout);
    }

    RowType &operator=(RowType &&rhs)
    {
        resizers = std::move(rhs.resizers);
        layout = std::move(rhs.layout);
        return *this;
    }

    void add(ColumnType &&newColumnDock, int position, Component* parent)
    {
        ValueTree column (Ids::Column);
        layoutTree.addChild(column, position, nullptr);
        rebuildResizers(parent); // TODO: this should go into the ValueTreeObjectList
    }

    /**
    Called from the docks resize method.

    @note this and the layoutRows() function are similar, but not similar enough...
    */
    void layoutColumns(const Rectangle<int> &area)
    {
        for (int i = 0; i < columns.size(); ++ i)
        {
            comps.push_back(columns[i].front());

            if (i < resizers.size())
                comps.push_back(resizers[i].get());
        }

        if (comps.size() == 1)
        {
            comps[0]->setBounds(area); // layoutComponents doesn't seem to cope with only one component passed to it.
        }
        else
        {
            layout->layOutComponents(comps.data(), static_cast<int>(comps.size()),
                                     area.getX(), area.getY(), area.getWidth(), area.getHeight(), false, true);
        }

        /* Make all other tabs match our new size...*/
        for (auto &c : columns)
        {
            if (c.size() > 1)
                for (auto &t : c)
                    t->setBounds(c[0]->getBounds());
        }
    }

    void rebuildResizers(Component* parent)
    {
        const double resizerWidth = 5.0;
        resizers.clear();

        int itemIndex = 0;

        for (int pos = 0; pos < columns.size(); ++ pos)
        {
            layout->setItemLayout(itemIndex ++, 10.0, 2000.0, columns[pos][0]->getWidth());

            if (pos < columns.size() - 1)
            {
                resizers.push_back(std::make_unique<StretchableLayoutResizerBar>(layout.get(), pos * 2 + 1, true));
                parent->addAndMakeVisible(resizers.back().get());
                layout->setItemLayout(itemIndex ++, resizerWidth, resizerWidth, resizerWidth);
            }
        }
    }

    ValueTree& layoutTree;
    std::unique_ptr<StretchableLayoutManager> layout;
    std::vector<std::unique_ptr<StretchableLayoutResizerBar>> resizers;
};


class RowList : public ValueTreeObjectList<RowType>
{
public:
    RowList(const juce::ValueTree &parentTree) : ValueTreeObjectList(parentTree)
    {
        rebuildObjects();
    }


    ~RowList() override
    {
        freeObjects();
    }

    bool isSuitableType(const juce::ValueTree &tree) const override
    {
        return tree.hasType(Ids::Row);
    }

    RowType* createNewObject(const juce::ValueTree &tree) override
    {
        RowType row;
    }

    void deleteObject(RowType* type) override
    {

    }

    void newObjectAdded(RowType* type) override
    {

    }

    void objectRemoved(RowType* type) override
    {

    }

    void objectOrderChanged() override
    {

    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RowList)
};

