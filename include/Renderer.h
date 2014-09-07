#pragma once

namespace wxstyle {

    // Forward declaration of StyledWindow
    class StyledWindow;

    /**
     *  Interface for a StyledWindow renderer.
     *
     *  This interface describes objects that are capable of drawing StyledWindows 
     *  through the Render method. Implementations of this interface can be
     *  registered with a StyledWindow object to have the drawing responsibility
     *  delegated.
     */
    class IRenderer {
    public:
        /**
         *  This method takes care of drawing a StyledWindow.
         */
        virtual void Render(StyledWindow* window) const = 0;

        virtual ~IRenderer() {};
    };

} // namespace wxstyle