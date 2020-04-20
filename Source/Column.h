/*
  ==============================================================================

    Column.h
    Created: 20 Apr 2020 11:49:53am
    Author:  Adam Wilson

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "Row.h"

class ColumnType
{
public:
    ColumnType(ValueTree& layoutTree) : layoutTree(layoutTree)
    {
    }

    int getWidth()
    {
        // TODO: return component width or find rows width. Most likely needs to be recursive.
        return 10;
    }

    void layoutRows(const Rectangle<int> &area)
    {
        std::vector<Component*> comps;

        for (int i = 0; i < rows.size(); ++ i)
        {
            comps.push_back(rows[i].columns.front().front());

            if (i < resizers.size())
                comps.push_back(resizers[i].get());
        }

        if (comps.size() == 1)
        {
            comps[0]->setBounds(area); // layoutComponents doesn't seem to cope with only one component passed to it.
        }
        else
        {
            layout.layOutComponents(comps.data(), comps.size(),
                                    area.getX(), area.getY(), area.getWidth(), area.getHeight(), true, false);
        }
    }

    ValueTree& layoutTree;
    std::unique_ptr<StretchableLayoutManager> layout;
    std::vector<RowType> rows;
    std::vector<std::unique_ptr<StretchableLayoutResizerBar>> resizers;

};
