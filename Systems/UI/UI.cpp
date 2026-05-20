#include "UI.hpp"

void UIButton::Draw() const
{
    DrawRectangleRec(rect, GRAY);

    int fontSize = 30;
    int textWidth = MeasureText(label.c_str(), fontSize);

    DrawText(
        label.c_str(),
        rect.x + rect.width / 2 - textWidth / 2,
        rect.y + rect.height / 2 - fontSize / 2,
        fontSize,
        WHITE
    );

    if (queuedCount > 0)
    {
        DrawText(
            TextFormat("%d", queuedCount),
            rect.x + rect.width - 12,
            rect.y - 5,
            18,
            WHITE
        );
    }
    if (progress >= 0.0f)
    {
        const float barHeight = 5.0f;

        Rectangle bg =
        {
            rect.x,
            rect.y - 10,
            rect.width,
            barHeight
        };

        Rectangle fill =
        {
            rect.x,
            rect.y - 10,
            rect.width * progress,
            barHeight
        };

        DrawRectangleRec(bg, DARKGRAY);
        DrawRectangleRec(fill, GREEN);
    }
}

void UIButton::HandleInput()
{

}

void UI::SetPanel(Rectangle p)
{
    panel = p;
}

void UI::AddButton(const UIButton& button)
{
    buttons.push_back(button);
}

void UI::Update()
{
    panel.x = 0;
    panel.y = GetScreenHeight() - 115;
    panel.width = GetScreenWidth();
    panel.height = 115;

    float padding = 20.0f;
    float size = 50.0f;

    float startX = panel.x + padding;
    float centerY = panel.y + (panel.height / 2.0f) - (size / 2.0f);

    for (size_t i = 0; i < buttons.size(); i++)
    {
        buttons[i].rect.x = startX + i * (size + padding);
        buttons[i].rect.y = centerY;
        buttons[i].rect.width = size;
        buttons[i].rect.height = size;
    }

    if (selectedBuilding &&
        !buttons.empty())
    {
        const BuildingDefinition& def =
            selectedBuilding
            ->GetDefinition();

        if (def.name == "Stables")
        {
            buttons[0].progress =
                selectedBuilding
                ->GetProductionProgress();

            buttons[0].queuedCount =
                selectedBuilding
                ->GetQueuedCount(
                    UnitType::Knight
                );
        }
        if (def.name == "Towncenter")
        {
            buttons[0].progress =
                selectedBuilding
                ->GetProductionProgress();

            buttons[0].queuedCount =
                selectedBuilding
                ->GetQueuedCount(
                    UnitType::Villager
                );
        }
    }
    // input handling
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();

        for (UIButton& b : buttons)
        {
            if (CheckCollisionPointRec(mouse, b.rect))
            {
                if (b.onClick)
                    b.onClick();
            }
        }
    }
}

void UI::Render()
{
    DrawRectangleRec(panel, DARKGRAY);

    // TITLE SECTION
    if (selectedBuilding)
    {
        const char* name = selectedBuilding->GetDefinition().name.c_str(); // or .name

        DrawText(
            name,
            panel.x + 20,
            panel.y - 21,
            25,
            WHITE
        );
    }

    // BUTTONS
    for (const UIButton& b : buttons)
        b.Draw();
}

void UI::Init()
{
    buttons.clear();

    // UI layout could be defined here later
    // but NOT game-specific buttons

    panel = {0,0,0,0};
}


void UI::SetSelectedBuilding(Building* b)
{
    selectedBuilding = b;
    Rebuild();
}

void UI::Rebuild()
{

	buttons.clear();
	
    if (!selectedBuilding)
        return;

    const BuildingDefinition& def = selectedBuilding->GetDefinition();

    for (UnitType type : def.producibleUnits)
    {
        UIButton button;

        button.unitType = type;

        const UnitDefinition& unitDef = UnitDatabase::Get(type);

        button.label = unitDef.name.c_str()[0];

        button.onClick = [this, type]()
        {
            selectedBuilding
            ->QueueUnit(type);
        };

        buttons.push_back(button);
    }

}

bool UI::IsMouseInside() const
{
    Vector2 mouse = GetMousePosition();

    return CheckCollisionPointRec(mouse, panel);
}