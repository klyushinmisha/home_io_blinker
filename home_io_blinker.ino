const char* serial_number = "19dc0663a1a14c22b0a73d2e35ee60ae";
const char* type = "blinker\r\n";

enum ProtocolState {
  initial, ack_conn, ack_serial, ack_type, sending
};

ProtocolState state;

void setup() {
  state = initial;
  Serial.begin(9600);
}

void loop() {
  if (state != sending) {
    initConnection();
  } else {
    byte data = 0xFF;
    Serial.write(data);
    delay(200);
  }
}

void initConnection() {
  String msg;
  switch (state) {
    case initial:
      Serial.print("ACK");
      msg = Serial.readString();
      if (msg == "ACK_CONN") {
        state = ack_conn;
      } else if (msg == "NACK") {
        state = initial;
      }
      break;
    case ack_conn:
      Serial.print(serial_number);
      msg = Serial.readString();
      if (msg == "ACK_SERIAL") {
        state = ack_serial;
      } else if (msg == "NACK") {
        state = initial;
      }
      break;
    case ack_serial:
      Serial.print(type);
      msg = Serial.readString();
      if (msg == "ACK_TYPE") {
        state = ack_type;
      } else if (msg == "NACK") {
        state = initial;
      }
      break;
    case ack_type:
      state = sending;
      break;
  }
}
