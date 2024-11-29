#include <iostream>
#include <thread>
#include <mosquitto.h>

#define BROKER_ADDRESS "test.mosquitto.org"
#define BROKER_PORT 1883
#define CLIENT_ID "test-client-id"
#define TOPIC "test/topic"

void message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
    std::cout << "Received message on topic: " << message->topic << std::endl;
    std::cout << "Message payload: " << (char*)message->payload << std::endl;
}

int main() {
    // Initialize the Mosquitto library
    mosquitto_lib_init();

    // Create a new Mosquitto client
    struct mosquitto *mosq = mosquitto_new(CLIENT_ID, true, nullptr);
    if (!mosq) {
        std::cerr << "Failed to create Mosquitto client" << std::endl;
        return -1;
    }

    // Set callback functions
    mosquitto_message_callback_set(mosq, message_callback);

    // Connect to the broker
    if (mosquitto_connect(mosq, BROKER_ADDRESS, BROKER_PORT, 60) != MOSQ_ERR_SUCCESS) {
        std::cerr << "Failed to connect to broker: " << BROKER_ADDRESS << std::endl;
        return -1;
    }
    std::cout << "Connected to broker " << BROKER_ADDRESS << std::endl;

    // Subscribe to a topic
    if (mosquitto_subscribe(mosq, nullptr, TOPIC, 0) != MOSQ_ERR_SUCCESS) {
        std::cerr << "Failed to subscribe to topic: " << TOPIC << std::endl;
        return -1;
    }
    std::cout << "Subscribed to topic: " << TOPIC << std::endl;

    // Start a background thread to handle communication (non-blocking)
    mosquitto_loop_start(mosq);

    // Publish a message to the topic (for debugging purposes)
    const char *message = "Hello from C++";
    mosquitto_publish(mosq, nullptr, TOPIC, strlen(message), message, 0, false);
    std::cout << "Message sent: " << message << std::endl;

    // Wait for some time to receive messages (in a real application, you might want this to be event-driven)
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        const char *message = "Hes alive!!";
        mosquitto_publish(mosq, nullptr, TOPIC, strlen(message), message, 0, false);
        std::cout << "Message sent: " << message << std::endl;
    }

    // Clean up and close the connection
    mosquitto_loop_stop(mosq, true);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}