add_executable(signal_test ../src/signaling.c test_signal.c unity_config.c)
target_link_libraries(signal_test PRIVATE
  pico_stdlib
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
  unity
)

pico_enable_stdio_uart(signal_test 0)
pico_enable_stdio_usb(signal_test 1)

add_executable(fifo_test ../src/fifo.c test_fifo.c unity_config.c)
target_link_libraries(fifo_test PRIVATE
  pico_stdlib
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
  unity
)

pico_enable_stdio_uart(fifo_test 0)
pico_enable_stdio_usb(fifo_test 1)

# The CYW43 is the Wifi/Bluetooth module. If the board is set to pico_w, this
# variable will be set and the wireless libraries added.
if(PICO_CYW43_SUPPORTED)
    target_link_libraries(signal_test PRIVATE
        pico_cyw43_arch_none
    )
    target_link_libraries(fifo_test PRIVATE
        pico_cyw43_arch_none
    )
endif()

# This will speed up the simulation, since data won't be copied from the flash controller.
# It does make the binary non-persistent on a real microcontroller.
# pico_set_binary_type(mytest no_flash)

find_program(RENODE renode
# This is extra stuff so it can find the mac installation paths.
 NAMES macos_run.command Renode.exe
 PATHS /Applications/Renode.app/Contents/MacOS)

set(RENODE_FLAGS
  --disable-xwt
  --port -2
  --pid-file renode.pid
  --console
  )

add_test(NAME simulate_mytest COMMAND
    ${RENODE}
     ${RENODE_FLAGS}
    -e "$ELF=@$<TARGET_FILE:signal_test>; $WORKING=@${CMAKE_SOURCE_DIR}; include @${CMAKE_SOURCE_DIR}/test/simulate.resc; start"
    )

    add_custom_target(flash_test_signal picotool load -f $<TARGET_FILE:signal_test> DEPENDS signal_test)
    add_custom_target(flash_test_fifo picotool load -f $<TARGET_FILE:fifo_test> DEPENDS fifo_test)
