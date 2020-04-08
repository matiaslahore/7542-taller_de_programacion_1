//
// Created by fperezboco on 4/11/19.
//

#ifndef MAP_PROMPT_H
#define MAP_PROMPT_H

#include "TrackList.h"
#include "../../editor/include/TrackEditor.h"
#include "TextTexture.h"
#include "../../editor/include/Window.h"
#include "Button.h"

#define PROMPT_FONT "../assets/fonts/OpenSans-Bold.ttf"
#define FIELD_FONT "../assets/fonts/OpenSans-Regular.ttf"
#define MSG_TRACK_NAME "Track name:"
#define MSG_TRACK_WIDTH "Track width (32 max. 2 min.):"
#define MSG_TRACK_HEIGHT "Track height (32 max. 2 min.):"
#define MSG_TOO_LARGE_NAME "Track name length limit reached."
#define MSG_TOO_LARGE_SIZE "Max size limit reached."
#define MSG_TOO_SHORT_NAME "Track name too short."
#define MSG_NAME_ALREADY_EXISTS "Track name already exists."
#define MSG_DIM_WIDTH "Track width invalid."
#define MSG_DIM_HEIGHT "Track height invalid."
#define SAVE_BUTTON_PATH "../assets/images/buttons/saveButton.png"
#define NEXT_BUTTON_PATH "../assets/images/buttons/nextButton.png"
#define EDIT_BUTTON_PATH "../assets/images/buttons/editButton.png"
#define NEW_BUTTON_PATH "../assets/images/buttons/newButton.png"
#define EXIT_BUTTON_PATH "../assets/images/buttons/exitButton.png"
#define HOME_BUTTON_PATH "../assets/images/buttons/homeButton.png"
#define WAY_BUTTON_PATH "../assets/images/buttons/wayButton.png"
#define SAVED_TICK_PATH "../assets/images/buttons/savedTick.png"
#define TITLE_PATH "../editor/images/title.png"

#define MAX_LENGTH_TRACK_NAME 30
#define MIN_LENGTH_TRACK_NAME 2
#define MAX_LENGTH_TRACK_DIMENSION 2
#define FONT_SIZE 40
#define PROMPTXSPACING 30
#define PROMPTYSPACING 20
#define MAX_TRACK_SIZE 32

class Prompt : TrackEditor {
private:
    Button editButton;
    Button nextButton;
    Button newButton;
    Button title;
    std::string inputText = " ";
    std::string nameError = " ";
    TextTexture textField{};
    TextTexture promptText{};
    TextTexture wrongText{};
    int textPosXPrompt = 0;
    int textPosXField = 0;
    int textPosYPrompt = 0;
    int textPosYField = 0;
    SDL_Color promptTextColor;
    SDL_Color fieldTextColor;
    SDL_Color wrongTextColor;
    bool modeAccepted = false;
    bool nameAccepted = false;
    bool widthAccepted = false;
    bool heightAccepted = false;
    bool returnPressed = false;
    bool renderText = false;
    bool textInput = false;
    bool backspacePressed = false;
    bool savePressed = false;
    bool editPressed = false;
    bool nextTrackPressed = false;
    bool newPressed = false;
    bool renderWrongMessage = false;
    bool lengthReached = false;
    bool createNewTrack = false;
    std::vector<std::string> trackNames;

public:
    Prompt();
    menuState inputTrackCharacteristics(Window &game) override;
    static bool trackExists(std::vector<std::string> &trackNames, const std::string &trackName);
    void processNameEvent(std::vector<std::string> &trackNames);
    void getNameEvent();
    void getNumberEvent();
    void processEventWidth();
    int toDimension();
    static bool inputDimensionGood(int dimSize);
    void initTextPrompt(SDL_Renderer *renderer, const std::string &promptString);
    void processTextPrompt(SDL_Renderer *renderer, bool &renderText);
    void renderTextPrompt(SDL_Renderer *renderer);
    int getTextFieldPosX();
    int getTextFieldPosY();
    void inputTrackName(Window &game);
    void inputTrackWidth(Window &game);
    bool isSDLNumber();
    void checkBackspaceAndReturn();
    bool isCtrlCommand();
    void processEventHeight();
    void inputTrackHeight(Window &game);
    void drawAll(Window &game);
    void setTextPosition();
    void createButtons(Window &game);
    void createTitle(Window &game);
    bool validNameSize();
    std::string getTrackName();
    int getWidth();
    int getHeight();

    void editOrNewTrack(Window &game);

    void getModeEvent();

    void processModeEvent();

    void drawMainMenu(Window &game);

    void
    updateTrackSelection(Window &window, const std::string &textToShow);

    void inputFileTrack(Window &game);

    void drawTrackSelection(Window &game);

    void processTrackSelectionEvent(std::vector<std::string>::iterator &track);

    void getTrackSelectionEvent();

    void renderTrackSelection(Window &window);
    void createHomeButton(Window & window);
};

#endif //MAP_PROMPT_H
