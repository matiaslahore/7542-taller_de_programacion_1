#ifndef __MATCHWINDOW_H__
#define __MATCHWINDOW_H__

#include <string>
#include <vector>
#include "sdl/SdlWindow.h"
#include "../../common/include/Button.h"
#include "sdl/SdlSurface.h"
#include "../../common/include/TextTexture.h"

typedef enum {
    selectingMode,
    creatingMatch,
    joiningMatch
} StateWindow;

class MatchWindow {
private:
    SdlWindow &window;
    StateWindow state = selectingMode;
    SdlSurface background;
    SdlSurface logo;
    Button createMatchButton;
    Button joinMatchButton;
    Button playButton;
    Button returnButton;
    Button arrowButton;
    Button arrowButton2;
    Button arrowButton3;
    TextTexture textTrack;
    TextTexture textPlayers;
    TextTexture textMatch;
    TextTexture textLua;
    std::vector<std::string> trackNames;
    std::vector<std::string>::iterator itTrackNames;
    std::vector<std::string> matchNames;
    std::vector<std::string>::iterator itMatchNames;
    std::vector<std::string> players;
    std::vector<std::string>::iterator itPlayers;
    std::vector<std::string> scripts;
    std::vector<std::string>::iterator itScripts;
    bool ready = false;
    bool returnClicked = false;

public:
    explicit MatchWindow(SdlWindow &sdlWindow);
    ~MatchWindow();
    void updateMatchButtons(const SDL_Event *event);
    void render();
    void setTrackNames(const std::vector<std::string>& tracks);
    StateWindow getState() const;
    std::string serializeData();
    bool isReady();
    void reset();
    bool isLuaSelected();
    bool isModeSelected();
    std::string getSelection();
    void setMatchNames(const std::vector<std::string>& matches);

    bool returnIsPressed();

    static std::string returnSerialized();

private:
    void createMatchButtons();
    void updateSelectingButtons(const SDL_Event *event);
    void updateNonSelectingButtons(const SDL_Event *event);
    void updateCreatingButtons(const SDL_Event *event);
    void showBackground();
    void selectingScreen();
    void creationScreen();
    void joiningScreen();
    /* Crea un selector a partir de la posicion x, y. Tiene un titulo (title),
     * un texto (textToShow), y un boton flecha para cambiar el texto
     * (buttonToChangeText). text es la textura donde se visualiza el
     * textToShow. Todas las posiciones de textos y botones se calculan dentro
     * de la función respecto al x, y. */
    void showSelectText(std::string title, std::string textToShow, int x, int y,
                        Button &buttonToChangeText, TextTexture &text);
    void showPlayAndReturn();
    void resetMatchButtons();

};

#endif
