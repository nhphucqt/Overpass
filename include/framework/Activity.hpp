#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include <ViewGroup.hpp>
#include <Intent.hpp>
#include <ActivityManager.hpp>
#include <EventPublisher.hpp>

class ActivityManager;

class Activity: public ViewGroup, 
                public EventPublisher {
friend class ActivityManager;

public: 
    typedef std::unique_ptr<Activity> Ptr;

public:
    enum ResultCode {
        RESULT_OK,
        RESULT_CANCELED
    };

private:
    ActivityManager* mManager;
    Intent::Ptr mIntent;
    int mResultCode;
    Intent::Ptr mResult;

public:
    Activity();
    virtual ~Activity();

    ActivityManager* getActivityManager();

protected:
    virtual void onEvent(const sf::Event& event);
    virtual void onCreate();
    virtual void onAttach();
    virtual void onResume();
    virtual void onPause();
    virtual void onDestroy();
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void onActivityResult(int requestCode, int resultCode, Intent::Ptr data);

    void startActivity(Ptr activity, Intent::Ptr intent);

    void startActivity(Ptr activity);

    Intent* getIntent();

    void setResult(int resultCode, Intent::Ptr data);

    void finish();
private:
    void setActivityManager(ActivityManager* manager);
    void setIntent(Intent::Ptr intent);
};

#endif