#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>

#define RESET_BUTTON_PIN 3

volatile bool resetRequested = false;

void IRAM_ATTR handleResetButtonPress() {
    resetRequested = true;
}

void setup(){
    Serial.begin(115200);
    Serial.println("Starting ESP32...");

    // Setup hardware reset button interrupt
    pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(RESET_BUTTON_PIN), handleResetButtonPress, FALLING);

    WiFiManager wm;

    // 1. Configure UI BEFORE calling autoConnect
    std::vector<const char*> menuItems = {"wifi", "exit"};
    wm.setMenu(menuItems);
    wm.setTitle("Consumer Portal WiFi Manager");

    const char* custom_css = 
        "<style>"
        "body { background-color: #121212; color: #ffffff; font-family: sans-serif; }"
        "button { background-color: #007bff; color: white; border: none; border-radius: 5px; padding: 10px 20px; }"
        "button:hover { background-color: #0056b3; }"
        "input { background-color: #333; color: #fff; border: 1px solid #555; border-radius: 3px; }"
        "a { color: #ffffff; text-decoration: none; font-weight: bold; }"
        "a:hover { color: #007bff; }"
        ".msg { color: #4caf50; }" 
        "</style>";
    wm.setCustomHeadElement(custom_css);

    wm.setConfigPortalTimeout(300);
    wm.setDebugOutput(true);

    // 2. Start connection / provisioning portal
    bool res = wm.autoConnect("ESP32_Config_AP", "pizza4tree");

    if (!res) {
        Serial.println("Failed to connect or portal timed out.");
        delay(3000);
        ESP.restart();
    } else {
        Serial.println("Connected to WiFi successfully!");
    }
}

void loop(){
    // Handle physical reset button press
    if (resetRequested) {
        Serial.println("Reset button pressed! Erasing WiFi credentials and restarting...");
        WiFiManager wm;
        wm.resetSettings();
        delay(500); 
        resetRequested = false;
        ESP.restart();
    }

    // Monitor WiFi state (non-blocking)
    static unsigned long lastCheck = 0;
    if (millis() - lastCheck > 10000) { // Check every 10 seconds instead of blocking delay
        lastCheck = millis();
        if (WiFi.status() != WL_CONNECTED) {
            Serial.println("WiFi disconnected. Reconnecting...");
            WiFi.reconnect();
        } else {
            Serial.print("WiFi Connected. IP: ");
            Serial.println(WiFi.localIP());
        }
    }
}