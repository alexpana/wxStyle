#pragma once

#include "StyledWindow.h"

namespace wxstyle
{
    class StyledTextBoxRenderer;

    class StyledTextBox : public StyledWindow
    {
    friend StyledTextBoxRenderer;

    public:
        StyledTextBox(wxWindow* parent = nullptr, wxString text = "", wxStandardID id = wxID_ANY);

        void OnMouseMoved(wxMouseEvent& mouseEvent) override;

        void OnMouseDown(wxMouseEvent& mouseEvent) override;

        void OnKeyPressed(wxKeyEvent& keyEvent) override;

        void OnKeyChar(wxKeyEvent& keyEvent) override;

        wxSize GetMinSize() const override;

        int GetCursorWidth() const;
         
        void SetCursorWidth(int width);

        size_t GetCursorPosition() const;

        void SetCursorPosition(size_t position);

        static Style GetDefaultStyle();

        // Selection methods

        int GetSelectionStart();

        int GetSelectionEnd();

        void SetSelection(int start, int end);

        void ClearSelection();

        wxString GetSelectedText();

        void RemoveSelectedText();

        bool HasSelectedText();

    private:
        std::string GetStdText();

        void GrowSelectionLeft();

        void GrowSelectionRight();

        void EnsureSelectionStarted();

        void SetSelectionEnd(int end);

        int FindCursorIndexFromPoint(int point);

        int FindCursorPointFromIndex();

        int GetTextRenderOffset();

        int GetTextAreaWidth();

        struct StyledTextBoxImpl;
        std::shared_ptr<StyledTextBoxImpl> pimpl;
    };
} // namespace wxstyle