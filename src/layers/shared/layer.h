class layer 
{
public:
    virtual void setup();
    virtual void load(int startAt, int stopAt);

    // playback control
    virtual void play();
    virtual void pause();
    virtual void stop();
};