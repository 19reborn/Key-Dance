typedef enum {
    INTERFACE_STATE_NULL, 
    INTERFACE_STATE_MAIN, 
    INTERFACE_STATE_MODE_SWITCH, 
    INTERFACE_STATE_MUSIC_SWITCH, 
    INTERFACE_STATE_SUMMARY,
    INTERFACE_STATE_TOT
} InterfaceState;

class InterfaceBase {
    public:
        static const int screenWidth = 800;
        static const int screenHeight = 450;

        virtual void init();
        virtual void update();
};

class InterfaceMain: public InterfaceBase {
    public:
        void init() {

        }

        void update() {

        }
}
