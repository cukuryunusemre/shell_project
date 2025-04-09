#include "controller.h"
#include "model.h"
#include "view.h"
#include <string.h>

void handle_user_input(const char *input) {
    if (strncmp(input, "@msg ", 5) == 0) {
        const char *msg = input + 5;
        send_message(msg);
    } else {
        char command_buffer[256];
        strncpy(command_buffer, input, sizeof(command_buffer));
        execute_command(command_buffer);
    }

    append_text_to_view(input);
}

