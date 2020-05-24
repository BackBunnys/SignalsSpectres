#include "States/InputState.h"
#include "States/WindowChooserState.h"

#include "FileExistingValidator.h"
#include "AccessingDataWrapper.h"

InputState::InputState(AppData &appData):
    State(appData), factory(appData) { }

InputState::~InputState() { }

void InputState::Init()
{
    bgColor = sf::Color(100, 100, 100);

    initGUI();
    initValidationHandler();
}

void InputState::initGUI()
{
    //////////////BUTTONS///////////////
    Button* nextButton = factory.getButton("Далее", [](AppData &appData){ appData.GetMachine()->getCurrentState()->NextState(); },
                                           sf::Vector2f(this->appData.GetWindow()->getSize().x / 5 * 4, this->appData.GetWindow()->getSize().y / 5 * 4));
    ////////////INPUTBOXES//////////////
    InputBox* filepath = factory.getInputBox(sf::Vector2u(800, 50), sf::Vector2f(this->appData.GetWindow()->getSize().x / 2,
                                                                                 this->appData.GetWindow()->getSize().y / 2));
    //////////////LABELS////////////////
    sf::Text* filepathLabel = this->factory.getText("Введите путь к файлу:", 30);
    filepathLabel->setPosition(filepath->getGlobalBounds().left, filepath->getGlobalBounds().top - 1.5 * filepathLabel->getGlobalBounds().height);
    ///////////GUI BINDINGS/////////////
    this->guiHandler.addInteractive("filepath", filepath);
    this->guiHandler.addInteractive("next", nextButton);

    this->guiHandler.addStatic(filepathLabel);
}

void InputState::initValidationHandler()
{
    sf::Text errorText("", appData.GetAssets()->getFont("Baltica Plain.001.001.ttf"), 30);
    errorText.setFillColor(sf::Color::Red);
    errorText.setPosition(this->appData.GetWindow()->getSize().x / 2 - errorText.getGlobalBounds().width / 2,
                          this->appData.GetWindow()->getSize().y / 8 * 5 - errorText.getGlobalBounds().height / 2);
    errorHandler.setText(errorText);
    errorHandler.addValidator(
        new FileExistingValidator(
            new AccessingDataWrapper<InputBox, std::string>(*static_cast<InputBox*>(guiHandler.getInteractiveElement("filepath")),
                                                                                    &InputBox::getInputtedText, "путь к файлу")));
}

void InputState::Update()
{
    this->guiHandler.update();
}

void InputState::Render(sf::RenderWindow& window)
{
    window.clear(bgColor);

    this->guiHandler.draw(window);
    this->errorHandler.draw(window);
}

void InputState::ProccessEvent(sf::Event &event)
{
    if(!this->guiHandler.processEvent(event))
        if(event.type == sf::Event::KeyPressed) {
            if(event.key.code == sf::Keyboard::Enter)
                NextState();
            else if(event.key.code == sf::Keyboard::Escape)
                this->appData.GetMachine()->PopState();
        }
}

void InputState::NextState()
{
    if(this->errorHandler.fullValidate()) {
        this->appData.setFilePath(static_cast<InputBox*>(guiHandler.getInteractiveElement("filepath"))->getInputtedText());

        this->appData.GetMachine()->PushState(new WindowChooserState(this->appData));
    }
}
