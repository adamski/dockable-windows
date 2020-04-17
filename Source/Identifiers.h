/*
  ==============================================================================

    Identifiers.h
    Created: 17 Apr 2020 4:32:55pm
    Author:  Adam Wilson

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include <unordered_map>

namespace Ids
{
#define DECLARE_ID(name)      const Identifier name (#name)

    // Types
    DECLARE_ID (Layout);
    DECLARE_ID (Row);
    DECLARE_ID (Column);
    DECLARE_ID (Component);

    // Properties
    DECLARE_ID (type);

#undef DECLARE_ID
};

namespace DockableComponentTypes
{
    struct DockableComponentInfo
    {
        String title;
        juce::Point<int> defaultSizeInUnits = {1, 1};
    };

    DockableComponentInfo info = { "test" };

    std::unordered_map<String, DockableComponentInfo> types { { "graph", {"Graph"}}, { "settings", {"Settings"}}, {"terminalFeed", {"Terminal Feed" }}};
}
