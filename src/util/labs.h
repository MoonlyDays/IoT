#define DEFINE_SETUP(n) void setup() { lab##n##_setup(); };
#define DEFINE_LOOP(n) void loop() { lab##n##_loop(); };
#define DEFINE_LAB(n) DEFINE_SETUP(n) DEFINE_LOOP(n)
#define DEFINE_LAB_NOLOOP(n) DEFINE_SETUP(n)
