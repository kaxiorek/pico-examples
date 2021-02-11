add_executable(raspPicoTest
        main.c
        dth11.c
        74HC565.c
        )

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(raspPicoTest pico_stdlib)
#target_link_libraries(raspPicoTest pico_stdlib hardware_pwm)

# enable usb output, disable uart output
pico_enable_stdio_usb(raspPicoTest 1)
pico_enable_stdio_uart(raspPicoTest 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(raspPicoTest)

# add url via pico_set_program_url
#example_auto_set_url(raspPicoTest)
