#ifndef SLEEPER_H
#define SLEEPER_H


class Sleeper {
public:
    Sleeper();
    ~Sleeper();
    static void sleep (long long delay);
    static void sleepMicro (long long delay);
};

#endif // SLEEPER_H
