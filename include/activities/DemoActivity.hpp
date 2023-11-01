#ifndef DEMO_ACTIVITY_HPP
#define DEMO_ACTIVITY_HPP

#include <Activity.hpp>
#include <RectangleView.hpp>

class DemoActivity: public Activity {
private:
    int id;
    RectangleView* mRect;

protected:
    virtual void onEvent(sf::Event& event) override;
    virtual void onCreate() override;
    virtual void onUpdate() override;
    virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void onAttach() override;
    virtual void onResume() override;
    virtual void onPause() override;
    virtual void onDestroy() override;
    virtual void onActivityResult(int requestCode, int resultCode, Intent::Ptr data) override;
};

#endif