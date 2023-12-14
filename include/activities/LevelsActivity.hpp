#ifndef LEVELS_ACTIVITY_HPP
#define LEVELS_ACTIVITY_HPP

#include <Activity.hpp>
#include <ResourceID.hpp>

#include <GameActivity.hpp>

class LevelsActivity : public Activity {
private:
    FontManager mFontManager;

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
    void createTitle();
    void createBackButton();
    void createLevelButtons();

    void enterGame(GameActivity::GameLevel level);
};

#endif