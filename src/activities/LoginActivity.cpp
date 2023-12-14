#include <LoginActivity.hpp>
#include <ActivityFactory.hpp>
#include <AppConfig.hpp>
#include <ResourceID.hpp>
#include <TextView.hpp>
#include <EditTextView.hpp>
#include <ButtonView.hpp>
#include <UserRepo.hpp>
#include <SignupActivity.hpp>

void LoginActivity::onLoadResources() {
    mFontManager.load(FontID::defaultFont, "res/fonts/Consolas-Bold.ttf");
}

void LoginActivity::onCreate() {
    createTitle();
    createBackButton();
    createDialog();
}

void LoginActivity::onAttach() {
    // ...
}

void LoginActivity::onResume() {
    // ...
}

void LoginActivity::onPause() {
    // ...
}

void LoginActivity::onDestroy() {
    // ...
}

void LoginActivity::onEvent(const sf::Event& event) {
    // ...
}

void LoginActivity::updateCurrent(sf::Time dt) {
    // ...
}

void LoginActivity::onActivityResult(int requestCode, int resultCode, Intent::Ptr data) {
    if (requestCode == REQUEST_SIGN_UP) {
        if (resultCode == (int)ResultCode::RESULT_OK) { 
            setResult((int)ResultCode::RESULT_OK, std::move(data));
            finish();
        } else if (resultCode == (int)ResultCode::RESULT_CANCELED) {
            mError->setText("Sign up failed");
        }
    }
}

void LoginActivity::createTitle() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    sf::Color color = sf::Color::Black;
    int fontSize = 50;

    TextView::Ptr title = std::make_unique<TextView>("Sign in", mFontManager.get(FontID::defaultFont), sf::Vector2f(), fontSize, color);
    sf::Vector2f position((windowSize.x-title->getGlobalBounds().getSize().x)/2, 50);
    title->setPosition(position);

    attachView(std::move(title));
}

void LoginActivity::createBackButton() {
    float width = 50;
    float height = 50;
    sf::Vector2f size(width, height);
    sf::Vector2f position(20, 20);
    sf::Color color = sf::Color(150, 150, 150, 255);
    int fontSize = 50;

    ButtonView::Ptr backButton = std::make_unique<ButtonView>(mFontManager.get(FontID::defaultFont), "<", fontSize, position, size, color);
    backButton->setTextColor(sf::Color::Black);
    backButton->setOnMouseButtonReleased(this, [&](EventListener* listener, const sf::Event& event) {
        setResult((int)ResultCode::RESULT_CANCELED, nullptr);
        finish();
    });
    attachView(std::move(backButton));
}

void LoginActivity::createDialog() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    float width = 300;
    float height = 100;
    sf::Vector2f size(width, height);
    // sf::Vector2f position((windowSize - size) / 2.f);
    sf::Vector2f position(windowSize.x/2 - width/2, 200);
    sf::Vector2f spacing(0, height + 20);
    sf::Color color = sf::Color(150, 150, 150, 255);

    EditTextView::Ptr usrField = std::make_unique<EditTextView>(this, mFontManager.get(FontID::defaultFont), "Username", position, size);
    EditTextView::Ptr pwdField = std::make_unique<EditTextView>(this, mFontManager.get(FontID::defaultFont), "Password", spacing, size);
    TextView::Ptr errorView = std::make_unique<TextView>("", mFontManager.get(FontID::defaultFont), spacing, 20, sf::Color::Red);
    usrField->setLimit(10);
    pwdField->setLimit(10);
    pwdField->setInputType(EditTextView::InputType::PASSWORD);

    mUsername = usrField.get();
    mPassword = pwdField.get();
    mError = errorView.get();

    ButtonView::Ptr submitButton = std::make_unique<ButtonView>(mFontManager.get(FontID::defaultFont), "Sign in", 20, sf::Vector2f(0, errorView->getCharacterSize() + 20), size, color);
    submitButton->setOnMouseButtonReleased(this, [&](EventListener* listener, const sf::Event& event) {
        checkLogin(mUsername->getText(), mPassword->getText());
    });

    ButtonView::Ptr registerButton = std::make_unique<ButtonView>(mFontManager.get(FontID::defaultFont), "Register", 20, spacing, size, color);
    registerButton->setOnMouseButtonReleased(this, [&](EventListener* listener, const sf::Event& event) {
        Intent::Ptr intent = Intent::Builder()
            .setRequestCode(REQUEST_SIGN_UP)
            .build();
        startActivity(ActivityFactory<SignupActivity>::createInstance(), std::move(intent));
    });

    submitButton->attachView(std::move(registerButton));
    errorView->attachView(std::move(submitButton));
    pwdField->attachView(std::move(errorView));
    usrField->attachView(std::move(pwdField));
    attachView(std::move(usrField));
}

void LoginActivity::checkLogin(const std::string& username, const std::string& password) {
    if (!username.empty() && !password.empty() && UserRepo::getInstance().checkUser(username, password)) {
        Intent::Ptr data = std::make_unique<Intent>();
        data->putExtra("username", username);
        setResult((int)ResultCode::RESULT_OK, std::move(data));
        finish();
    } else {
        mError->setText("Invalid username or password");
    }
}