#include "StyledTextBox.h"

#include <wx/clipbrd.h>

#include "style\draw\DrawRectangleInstruction.h"
#include "style\draw\DrawTextInstruction.h"

#include "DimPoint.h"
#include "DimRect.h"
#include "FontMetrics.h"
#include "Insets.h"
#include "StylesheetRenderer.h"

namespace wxstyle
{
    struct StyledTextBox::StyledTextBoxImpl {
        int selectionStartIndex;
        int selectionEndIndex;
        int textOffset;
        size_t cursorPosition;
        int cursorWidth;

        StyledTextBoxImpl() : 
            selectionStartIndex(0), 
            selectionEndIndex(0), 
            textOffset(0), 
            cursorPosition(0), 
            cursorWidth(1)
        {
        }
    };

    class StyledTextBoxRenderer : public StylesheetRenderer {
        virtual void Render(StyledWindow* window) const {
            wxAutoBufferedPaintDC deviceContext(window);

            auto textBox = static_cast<StyledTextBox*>(window);
            auto g = std::unique_ptr<wxGraphicsContext>(wxGraphicsContext::Create(deviceContext));

            auto context = g.get();

            DrawBackground(context, textBox);
            DrawSelection(context, textBox);
            DrawText(context, textBox);
            DrawCursor(context, textBox);
        }

        void DrawSelection(wxGraphicsContext* g, StyledTextBox* textBox) const {
            g->Clip(
                textBox->GetInsets().Left(), 
                textBox->GetInsets().Top(), 
                textBox->GetSize().GetWidth() - textBox->GetInsets().Width(), 
                textBox->GetSize().GetHeight() - textBox->GetInsets().Height());

            wxString prefixText = textBox->GetText().Mid(0, textBox->GetSelectionStart());
            wxString selectedText = textBox->GetSelectedText();

            TextMetrics metrics(textBox);

            wxSize textSize = metrics.GetTextSize(
                prefixText, 
                textBox->GetDefinitionBundle().GetFont());

            int textWidth = metrics.GetTextSize(
                selectedText,
                textBox->GetDefinitionBundle().GetFont()).GetWidth();

            int x = textSize.GetWidth() + textBox->GetInsets().Left() + textBox->GetTextRenderOffset();
            int y = textBox->GetInsets().Top();
            int w = textWidth;
            int h = textBox->GetSize().GetHeight() - textBox->GetInsets().Height();

            DrawRectangleInstruction(DrawRectangleInstruction::Params()
                .SetRect(DimRect(x, y, w, h))
                .SetColor("#0d5c91"))
                .Draw(g, textBox->GetSize());

            g->ResetClip();
        }

        void DrawText(wxGraphicsContext* g, StyledTextBox* textBox) const {
            // set clipping region
            g->Clip(
                textBox->GetInsets().Left(), 
                textBox->GetInsets().Top(), 
                textBox->GetSize().GetWidth() - textBox->GetInsets().Width(), 
                textBox->GetSize().GetHeight() - textBox->GetInsets().Height());

            DrawTextInstruction(DrawTextInstruction::Params()
                .SetHorizontalAnchor(HA_LEFT)
                .SetVerticalAnchor(VA_CENTER)
                .SetTextPosition(DimPoint(textBox->GetInsets().Left() + textBox->GetTextRenderOffset(), Dimension(0, 0.5)))
                .SetFontDefinition(textBox->GetDefinitionBundle().GetFont())
                .SetText(textBox->GetText())
                .SetTextColor(textBox->GetDefinitionBundle().GetForegroundColor()))
                .Draw(g, textBox->GetSize());

            g->ResetClip();
        }

        void DrawCursor(wxGraphicsContext* g, StyledTextBox* textBox) const {
            if (textBox->IsFocused()) {
                int x = textBox->FindCursorPointFromIndex() + textBox->GetInsets().Left();
                int y = textBox->GetInsets().Top();
                int w = textBox->GetCursorWidth();
                int h = textBox->GetSize().GetHeight() - textBox->GetInsets().Height();

                DrawRectangleInstruction(DrawRectangleInstruction::Params()
                    .SetRect(DimRect(x, y, w, h))
                    .SetColor("#AAAAAA"))
                    .Draw(g, textBox->GetSize());
            }
        }
    };

    Style StyledTextBox::GetDefaultStyle() {
        Style result = GetStyle();

        // DEFAULT
        DefinitionBundle defaultBundle = result.GetBundle(Style::CAT_DEFAULT);

        std::vector<DrawInstruction*> defaultDrawInstructions;

        defaultDrawInstructions.push_back(
            new DrawRectangleInstruction(DrawRectangleInstruction::Params()
                .SetRect(DimRect(0, 0, Dimension(0, 1), Dimension(0, 1)))
                .SetColor("#4e4c4c")));

        defaultDrawInstructions.push_back(
            new DrawRectangleInstruction(DrawRectangleInstruction::Params()
            .SetInsets(0, 0, 0, 1)
            .SetColor("#1c1617")));

        defaultDrawInstructions.push_back(
            new DrawRectangleInstruction(DrawRectangleInstruction::Params()
                .SetInsets(1, 1, 1, 2)
                .SetColor("#2b2a2a")));

        defaultBundle.SetDrawInstructions(defaultDrawInstructions);

        // FOCUSED
        DefinitionBundle focusedBundle = result.GetBundle(Style::CAT_FOCUSED);

        std::vector<DrawInstruction*> focusedDrawInstructions;

        focusedDrawInstructions.push_back(
            new DrawRectangleInstruction(DrawRectangleInstruction::Params()
            .SetRect(DimRect(0, 0, Dimension(0, 1), Dimension(0, 1)))
            .SetColor("#4e4c4c")));

        focusedDrawInstructions.push_back(
            new DrawRectangleInstruction(DrawRectangleInstruction::Params()
            .SetInsets(0, 0, 0, 1)
            .SetColor("#007acc")));

        focusedDrawInstructions.push_back(
            new DrawRectangleInstruction(DrawRectangleInstruction::Params()
            .SetInsets(1, 1, 1, 2)
            .SetColor("#2b2a2a")));

        focusedBundle.SetDrawInstructions(focusedDrawInstructions);

        result.AddBundle(Style::CAT_DEFAULT, defaultBundle);
        result.AddBundle(Style::CAT_FOCUSED, focusedBundle);

        return result;
    }

    StyledTextBox::StyledTextBox(wxWindow* parent, wxString text, wxStandardID id)
        : StyledWindow(parent, text ,id)
    {
        pimpl = std::make_shared<StyledTextBoxImpl>();
        SetWindowStyle(GetWindowStyle() | wxWANTS_CHARS);

        SetRenderer(std::make_shared<StyledTextBoxRenderer>());
        SetStyle(StyledTextBox::GetDefaultStyle());

        SetInsets(Insets(3, 3, 3, 3));
        SetMinSize(wxSize(0, 22));
    }

    wxSize StyledTextBox::GetMinSize() const {
        int width = 0;
        int height = 0;

        TextMetrics textMetrics = TextMetrics(const_cast<StyledTextBox*>(this));

        int fontHeight = textMetrics.GetFontMetrics().height;

        width += GetInsets().Width();

        height += GetInsets().Height();
        height += fontHeight;

        wxSize userMinSize = StyledWindow::GetMinSize();
        return wxSize(std::max(width, userMinSize.GetWidth()), std::max(height, userMinSize.GetHeight()));
    }

    void StyledTextBox::OnKeyChar(wxKeyEvent& keyEvent) {
        // Process visible character input

        if (!keyEvent.HasModifiers()) {
            int keycode = keyEvent.GetRawKeyCode();

            if (keycode < 255 && isprint(keycode)) {
                if (HasSelectedText()) {
                    RemoveSelectedText();
                }

                char c = (wxChar)keycode;
                auto text = GetStdText();

                auto insertPosition = begin(text) + GetCursorPosition();

                text.insert(insertPosition, c);

                SetText(text);

                SetCursorPosition(GetCursorPosition() + 1);
            }
        }
    }

    void StyledTextBox::OnKeyPressed(wxKeyEvent& keyEvent) {

        bool eventHandled = false;
        int keycode = keyEvent.GetKeyCode();
        int originalCursorPosition = GetCursorPosition();

        // Used to indicate there was a cursor navigation event
        bool navigationEvent = false;

        if (keyEvent.GetModifiers() & wxMOD_SHIFT) {
            EnsureSelectionStarted();
        }

        // Select All
        if (keyEvent.ControlDown() && keycode == 'A') {
            SetCursorPosition(GetText().Length());
            SetSelection(0, 0);
            SetSelectionEnd(GetCursorPosition());
            eventHandled = true;
        }

        // Copy
        if (keyEvent.ControlDown() && keycode == 'C') {
            if (wxTheClipboard->Open())
            {
                wxTheClipboard->SetData(new wxTextDataObject(GetSelectedText()));
                wxTheClipboard->Close();
            }
            eventHandled = true;
        }

        // Paste
        if (keyEvent.ControlDown() && keycode == 'V') {
            if (wxTheClipboard->Open())
            {
                if (wxTheClipboard->IsSupported(wxDF_TEXT))
                {
                    wxTextDataObject data;
                    wxTheClipboard->GetData(data);
                    if (HasSelectedText()) {
                        RemoveSelectedText();
                    }
                    auto text = GetText();
                    text.insert(GetCursorPosition(), data.GetText());
                    SetText(text);
                    SetCursorPosition(GetCursorPosition() + data.GetText().Length());
                }
                wxTheClipboard->Close();
            }
        }

        if (keycode == WXK_BACK) {
            if (HasSelectedText()) {
                RemoveSelectedText();
            } else if (GetCursorPosition() > 0) {
                auto text = GetStdText();

                auto eraseStart = begin(text) + GetCursorPosition() - 1;
                auto eraseEnd = eraseStart + 1;
                text.erase(eraseStart, eraseEnd);

                SetText(text);

                SetCursorPosition(GetCursorPosition() - 1);
            }
            eventHandled = true;
            navigationEvent = true;
        }

        if (keycode == WXK_DELETE) {
            if (HasSelectedText()) {
                RemoveSelectedText();
            } else if (GetCursorPosition() < GetText().Length()) {
                auto text = GetStdText();

                auto eraseStart = begin(text) + GetCursorPosition();
                auto eraseEnd = eraseStart + 1;
                text.erase(eraseStart, eraseEnd);

                SetText(text);
            }
            return;
        } 

        if (keycode == WXK_LEFT) {
            if (GetCursorPosition() > 0) {
                SetCursorPosition(GetCursorPosition() - 1);
            }
            eventHandled = true;
            navigationEvent = true;
        }

        if (keycode == WXK_RIGHT) {
            if (GetCursorPosition() < GetText().Length()) {
                SetCursorPosition(GetCursorPosition() + 1);
            }
            eventHandled = true;
            navigationEvent = true;
        }

        if (keycode == WXK_END) {
            SetCursorPosition(GetText().Length());
            eventHandled = true;
            navigationEvent = true;
        }

        if (keycode == WXK_HOME) {
            SetCursorPosition(0);
            eventHandled = true;
            navigationEvent = true;
        }

        if (keyEvent.GetModifiers() & wxMOD_SHIFT) {
            SetSelectionEnd(GetCursorPosition());
        } else {
            if (navigationEvent) {
                ClearSelection();
            }
        }

        if (!eventHandled) {
            keyEvent.Skip();
        }

        Refresh();
    }

    void StyledTextBox::OnMouseMoved(wxMouseEvent& mouseEvent) {
        if (mouseEvent.ButtonIsDown(wxMOUSE_BTN_LEFT)) {
            EnsureSelectionStarted();
            SetSelectionEnd(FindCursorIndexFromPoint(mouseEvent.GetX()));
            pimpl->cursorPosition = pimpl->selectionEndIndex;
            Refresh();
        }
    }

    int StyledTextBox::FindCursorIndexFromPoint(int point) {
        int position = -pimpl->textOffset;
        wxString currentString = "";
        TextMetrics metrics(const_cast<StyledTextBox*>(this));

        for (auto c : GetText()) {
            currentString += c;
            if (GetInsets().Left() + metrics.GetTextSize(currentString, GetDefinitionBundle().GetFont()).GetWidth() > point)
            {
                break;
            }
            position += 1;
        }

        return position;
    }

    void StyledTextBox::OnMouseDown(wxMouseEvent& mouseEvent) {
        if (HasFocus()) {
            ClearSelection();
            pimpl->cursorPosition = FindCursorIndexFromPoint(mouseEvent.GetX());
        } else {
            SetFocus();
        }
    }

    int StyledTextBox::GetCursorWidth() const {
        return pimpl->cursorWidth;
    }

    void StyledTextBox::SetCursorWidth(int width) {
        pimpl->cursorWidth = width;
    }

    size_t StyledTextBox::GetCursorPosition() const {
        return pimpl->cursorPosition;
    }

    void StyledTextBox::SetCursorPosition(size_t position) {
        if (position < 0 || position > GetText().Length()) {
            return;
        }

        int remainingText = GetTextAreaWidth() - FindCursorPointFromIndex();

        if (position == GetText().Length()) {
            pimpl->textOffset = std::min(0, pimpl->textOffset + remainingText);
        }

        pimpl->cursorPosition = position;

        // recalculate text offset
        int cursorOffset = FindCursorPointFromIndex();
        int textAreaWidth = GetTextAreaWidth();

        if (cursorOffset < 0 || cursorOffset > textAreaWidth) {
            if (cursorOffset > textAreaWidth) cursorOffset -= textAreaWidth;
            pimpl->textOffset -= cursorOffset;
        }
    }

    int StyledTextBox::GetSelectionStart() {
        return std::min(pimpl->selectionStartIndex, pimpl->selectionEndIndex);
    }

    int StyledTextBox::GetSelectionEnd() {
        return std::max(pimpl->selectionStartIndex, pimpl->selectionEndIndex);
    }

    void StyledTextBox::SetSelection(int start, int end) {
        pimpl->selectionStartIndex = start;
        pimpl->selectionEndIndex = end;
        Refresh();
    }

    wxString StyledTextBox::GetSelectedText() {
        return GetText().SubString(GetSelectionStart(), GetSelectionEnd() - 1);
    }

    std::string StyledTextBox::GetStdText() {
        return GetText().ToStdString();
    }

    void StyledTextBox::ClearSelection() {
        pimpl->selectionStartIndex = 0;
        pimpl->selectionEndIndex = 0;
        Refresh();
    }

    void StyledTextBox::RemoveSelectedText() {
        if (!HasSelectedText()) {
            return;
        }

        auto text = GetStdText();
        auto eraseStart = begin(text) + GetSelectionStart();
        auto eraseEnd = eraseStart + (GetSelectionEnd() - GetSelectionStart());

        text.erase(eraseStart, eraseEnd);

        SetCursorPosition(GetSelectionStart());

        SetText(text);

        ClearSelection();
    }

    bool StyledTextBox::HasSelectedText() {
        return GetSelectionStart() - GetSelectionEnd() != 0;
    }

    void StyledTextBox::GrowSelectionLeft() {
        EnsureSelectionStarted();
        SetSelectionEnd(pimpl->selectionEndIndex - 1);
        SetCursorPosition(pimpl->selectionEndIndex);
        Refresh();
    }

    void StyledTextBox::GrowSelectionRight() {
        EnsureSelectionStarted();
        SetSelectionEnd(pimpl->selectionEndIndex + 1);
        SetCursorPosition(pimpl->selectionEndIndex);
        Refresh();
    }

    void StyledTextBox::EnsureSelectionStarted() {
        if (!HasSelectedText()) {
            SetSelection(GetCursorPosition(), GetCursorPosition());
        }
    }

    void StyledTextBox::SetSelectionEnd(int end) {
        if (end >= 0 && (unsigned) end <= GetText().Length()) {
            pimpl->selectionEndIndex = end;
        }
    }

    int StyledTextBox::FindCursorPointFromIndex() {
        TextMetrics textMetrics = TextMetrics(const_cast<StyledTextBox*>(this));
        return textMetrics.GetTextSize(GetText().SubString(0, GetCursorPosition() - 1), GetDefinitionBundle().GetFont()).GetWidth() + pimpl->textOffset;
    }

    int StyledTextBox::GetTextRenderOffset() {
        return pimpl->textOffset;
    }

    int StyledTextBox::GetTextAreaWidth() {
        return GetSize().GetWidth() - GetInsets().Width();
    }
} // namespace wxstyle
