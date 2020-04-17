/*

  ==============================================================================

	ArrangeableDock.h
	Created: 6 Jul 2016 10:27:02pm
	Author:  jim

  ==============================================================================
*/

#ifndef ADVANCEDDOCK_H_INCLUDED
#define ADVANCEDDOCK_H_INCLUDED

#include <unordered_map>
#include "JDockableWindows.h"

namespace Ids
{
    const Identifier AppSettings("Settings");

#define DECLARE_ID(name)      const Identifier name (#name)

    // Types
    DECLARE_ID (Layout);
    DECLARE_ID (Row);
    DECLARE_ID (Column);
    DECLARE_ID (Component);

    // Properties
    DECLARE_ID (type);

#undef DECLARE_ID

//    // TODO: Use code generation to fill the graph types
//#define DECLARE_STRING(name)      const String name (#name);
//
//    DECLARE_STRING(graph); // TODO: This will become temperatureGraph etc
//    DECLARE_STRING(settings);
//    DECLARE_STRING(terminal);
//    DECLARE_STRING(empty);  // Test only. TODO: Remove
//
//#undef DECLARE_STRING
//
//    static std::vector<String> validComponentTypes { graph, settings, terminal, empty };


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

namespace ArrangeableDockPlaces
{
    enum Places
    {
        top, left, right, bottom, none
    };
};

class ArrangeableDockPlacementDialog;

/**
The arrangeable dock allows vertical and horizontal splits
*/
class ArrangeableDock
        : public Component,
          private ValueTree::Listener,
          DockBase
{
public:
    ArrangeableDock(DockableWindowManager &manager_);

    ~ArrangeableDock();;

    /** Adds a component to the dock so it's visible to the user.
     
     We assume you are managing the components lifetime.  However an optional 
     change could be to have the DockManager manage them.
     */
    void addComponentToDock(Component* component);

    /** Adds a component to the dock so it's visible to the user.
     
     @param rowPosition - where to insert the new row.  If rowPosition is -1 it
     will be inserted at the bottom. Rows are numbered from the top down.  A row 
     position of 0 will insert the component at the top. */
    void addComponentToNewRow(Component* component, int rowPosition);


    void resized() override;

    void paint(Graphics &g) override;

private:
    struct WindowLocation
    {
        WindowLocation(int y, int x, int t);

        int y{0};
        int x{0};
        int tab{0};
    };

    WindowLocation getWindowLocationAtPoint(const Point<int> &screenPosition);

    Rectangle<int> getWindowBoundsAtPoint(const Point<int> &p);

    /**
    Insert a new window in to the right place in our dock...
    */
    void insertWindow(const Point<int> &screenPos, ArrangeableDockPlaces::Places places, DockableComponentWrapper* comp);

    void showDockableComponentPlacement(DockableComponentWrapper* component, Point<int> screenPosition) override;

    void hideDockableComponentPlacement() override;

    void startDockableComponentDrag(DockableComponentWrapper* component) override;

    void insertNewColumn(DockableComponentWrapper* comp, ArrangeableDock::WindowLocation loc);

    void insertNewRow(DockableComponentWrapper* comp, ArrangeableDock::WindowLocation loc);

    bool attachDockableComponent(DockableComponentWrapper* component, Point<int> screenPosition) override;

    void detachDockableComponent(DockableComponentWrapper* component) override;

    void revealComponent(DockableComponentWrapper* dockableComponent) override;

    class RowType;

    class ColumnType;

    ValueTree layoutTree;

    std::vector<RowType> rows;
    std::vector<std::unique_ptr<StretchableLayoutResizerBar>> resizers;
    StretchableLayoutManager layout;

    void rebuildRowResizers();

    void layoutRows(const Rectangle<int> &area);

    DockableWindowManager &manager;
    std::unique_ptr<ArrangeableDockPlacementDialog> placementDialog;
};


#endif  // ADVANCEDDOCK_H_INCLUDED
