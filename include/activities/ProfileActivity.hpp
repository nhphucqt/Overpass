#ifndef PROFILE_ACTIVITY_HPP
#define PROFILE_ACTIVITY_HPP

#include <Activity.hpp>
#include <ResourceID.hpp>
#include <UserSession.hpp>
#include <SpriteView.hpp>

class ProfileActivity: public Activity {
private:
    static const int REQUEST_LOG_IN = 11;
    static const int REQUEST_TITLEBAR_BUTTONS = 126;

    FontManager mFontManager;
    TextureManager mTextureManager;

protected:
    virtual void onEvent(const sf::Event& event) override;
    virtual void onCreate() override;
    virtual void onLoadResources() override;
    virtual void onAttach() override;
    virtual void onResume() override;
    virtual void onPause() override;
    virtual void onDestroy() override;
    void updateCurrent(sf::Time dt) override;
    virtual void onActivityResult(int requestCode, int resultCode, Intent::Ptr data) override;

private:
    void createBackButton();
    void createBackground();
    void createTitle();
    void createProfile();   
    void createGuessProfile(SpriteView* dialog);
    void createUserProfile(SpriteView* dialog);
};

#endif