// Set pins
int led = D7;
int zpin = A1;
int gpin = A2;
int ppin = A0;

// boolean running = false;
int start_time = 0;
int stop_time = 0;

void setup() {
    // Set led, ground and power as output
    pinMode(led, OUTPUT);
    pinMode(gpin, OUTPUT);
    pinMode(ppin, OUTPUT);
    // Turn on power and ground
    digitalWrite(gpin, LOW); 
    digitalWrite(ppin, HIGH);
    delay(1000);
}

void loop() {
    if (is_running() == true) { // if device is moving
        digitalWrite(led, HIGH);
        
        // if it wasn't moving before
        if (start_time == 0) { 
            // set start_time
            start_time = Time.now();
            Spark.publish("Start Time", String(start_time));
        }
        
        // reset stop_time
        stop_time = 0;
    } else { // if device isn't moving
        digitalWrite(led, LOW);
        
        // if device has been moving
        if (start_time > 0) {
           // if stop_time hasn't been set
            if (stop_time == 0) {
                // set stop_time
                stop_time = Time.now();
            } else if (Time.now() - stop_time > 5) { // if stop_time was at more than 5 seconds ago
                int total_time = stop_time - start_time;
                
                // if total run time was more than a minute
                if (total_time > 60) { // 1 minute
                // if (total_time > 5) { // 5 seconds
                    // publish event
                    int minutes = total_time / 60;
                    int seconds = total_time % 60;
                    Spark.publish("Running Stopped", String(minutes) + "m " + String(seconds) + "s");
                    Spark.publish("Stop Time", String(stop_time));
                }
                
                // reset start_time
                start_time = 0;
            }
        }
    }
    delay(500);
}

// Is the accelerometer moving?
// Check Z axis a number of times, if the highest value and lowest value is over a threshold, report it is moving
boolean is_running() {
    int high = 0;
    int low = 0;
    // Check the Z axis 15 times over roughly 2 seconds
    // record highest and lowest values
    for(int i=0; i<15; i++) {
        int val = analogRead(zpin);
        if (val > high) {
           high = val; 
        } else if (val < low) {
            low = val;
        }
        
        if (i == 0) {
            low = high;
        }
        
        delay(200);
    }
    
    // if difference in values is higher than threshold, accelerometer is moving
    int difference = high - low;
    Spark.publish("Z-Axis Difference", String(difference));
    if (difference > 10) {
        return true;
    } else {
        return false;
    }
}
