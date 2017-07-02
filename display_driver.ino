volatile bool wasLD1High = false;
volatile bool wasLD2High = false;
volatile char incomingData = 0;

void OnLD1PinHigh () {
  wasLD1High = true;
  wasLD2High = false;

  incomingData = (PINB & B00001111) | (PIND & B11110000);
}

void OnLD2PinHigh () {
  wasLD1High = false;
  wasLD2High = true;

  incomingData = (PINB & B00001111) | (PIND & B11110000);
}

// Input pins          0  1  2  3  4  5  6   7
const byte inputs[] = {4, 5, 6, 7, 8, 9, 10, 11};

// LD pins
const byte LD1 = 2;
const byte LD2 = 3;

byte i = 0;

void setup () {
  for (i = 0; i < 8; i++) {
    pinMode(inputs[i], INPUT_PULLUP);
  }

  pinMode(LD1, INPUT);
  pinMode(LD2, INPUT);

  // Attach interrupts
  attachInterrupt(digitalPinToInterrupt(LD1), OnLD1PinHigh, RISING);
  attachInterrupt(digitalPinToInterrupt(LD2), OnLD2PinHigh, RISING);

  Serial.begin(115200);
  Serial.println("Start of output");
}

byte line1Index = 0;
byte line2Index = 0;

char line1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
char line2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

bool inControlMode = false;
bool line1Done = false;
bool line2Done = false;

void loop () {
  if (wasLD1High) {
    processCommand(incomingData, line1, line1Index);
    wasLD1High = false;
  }

  if (wasLD2High) {
    processCommand(incomingData, line2, line2Index);
    wasLD2High = false;
  }

  if (line1[20] && line2[20]) {
    line1[20] = 0;
    line2[20] = 0;

    Serial.println("Display 1:");
    for (i = 0; i < 20; i++) {
      printCharacter(line1[i]);
    }
    Serial.println(' ');

    Serial.println("Display 2:");
    for (i = 0; i < 20; i++) {
      printCharacter(line2[i]);
    }
    Serial.println(' ');
  }
}

// Function call will copy the value set in command, so it won't change during an interrupt
void processCommand(char command, char* lineData, byte& index) {
  if (inControlMode) {
    Serial.println("Now in control mode");

    // Write 0x01 to the line if this command is given
    if (command == B0000001) {
      insertCharacterInLine(lineData, index, command);
    }
    // Else just print the command given
    else {
      Serial.print("Command given in control mode: ");
      Serial.println(command, HEX);
    }

    inControlMode = false;
  }
  else {
    if (command == B00000001) {
      Serial.println("! Went into control mode");
      inControlMode = true;
    }
    else {
      insertCharacterInLine(lineData, index, command);
    }
  }
}

void insertCharacterInLine(char* lineData, byte& index, char command) {
  lineData[index] = B01111111 & command;
  index++;

  if (index == 20) {
    index = 0;
    lineData[20] = 1;
  }
}

void printCharacter (char character) {
  switch (character) {
    case 0x00:
    case 0x01:
    case 0x20:
      Serial.print(' ');
      break;
    case 0x02:
      Serial.print("0,");
      break;
    case 0x03:
      Serial.print("1,");
      break;
    case 0x04:
      Serial.print("2,");
      break;
    case 0x05:
      Serial.print("3,");
      break;
    case 0x06:
      Serial.print("4,");
      break;
    case 0x07:
      Serial.print("5,");
      break;
    case 0x08:
      Serial.print("6,");
      break;
    case 0x09:
      Serial.print("7,");
      break;
    case 0x0A:
      Serial.print("8,");
      break;
    case 0x0B:
      Serial.print("9,");
      break;
    case 0x0C:
      Serial.print("0.");
      break;
    case 0x0D:
      Serial.print("1.");
      break;
    case 0x0E:
      Serial.print("2.");
      break;
    case 0x0F:
      Serial.print("3.");
      break;
    case 0x10:
      Serial.print("4.");
      break;
    case 0x11:
      Serial.print("5.");
      break;
    case 0x12:
      Serial.print("6.");
      break;
    case 0x13:
      Serial.print("7.");
      break;
    case 0x14:
      Serial.print("8.");
      break;
    case 0x15:
      Serial.print("9.");
      break;
    case 0x16:
      Serial.print("0.,");
      break;
    case 0x17:
      Serial.print("1.,");
      break;
    case 0x18:
      Serial.print("2.,");
      break;
    case 0x19:
      Serial.print("3.,");
      break;
    case 0x1A:
      Serial.print("4.,");
      break;
    case 0x1B:
      Serial.print("5.,");
      break;
    case 0x1C:
      Serial.print("6.,");
      break;
    case 0x1D:
      Serial.print("7.,");
      break;
    case 0x1E:
      Serial.print("8.,");
      break;
    case 0x1F:
      Serial.print("9.,");
      break;
    case 0x21:
      Serial.print('!');
      break;
    case 0x22:
      Serial.print('"');
      break;
    case 0x23:
      Serial.print('#');
      break;
    case 0x24:
      Serial.print('$');
      break;
    case 0x25:
      Serial.print('%');
      break;
    case 0x26:
      Serial.print('&');
      break;
    case 0x27:
      Serial.print('\'');
      break;
    case 0x28:
      Serial.print('(');
      break;
    case 0x29:
      Serial.print(')');
      break;
    case 0x2A:
      Serial.print('*');
      break;
    case 0x2B:
      Serial.print('+');
      break;
    case 0x2C:
      Serial.print(',');
      break;
    case 0x2D:
      Serial.print('-');
      break;
    case 0x2E:
      Serial.print('.');
      break;
    case 0x2F:
      Serial.print('/');
      break;
    case 0x30:
      Serial.print('0');
      break;
    case 0x31:
      Serial.print('1');
      break;
    case 0x32:
      Serial.print('2');
      break;
    case 0x33:
      Serial.print('3');
      break;
    case 0x34:
      Serial.print('4');
      break;
    case 0x35:
      Serial.print('5');
      break;
    case 0x36:
      Serial.print('6');
      break;
    case 0x37:
      Serial.print('7');
      break;
    case 0x38:
      Serial.print('8');
      break;
    case 0x39:
      Serial.print('9');
      break;
    case 0x3A:
      Serial.print(':');
      break;
    case 0x3B:
      Serial.print(';');
      break;
    case 0x3C:
      Serial.print('<');
      break;
    case 0x3D:
      Serial.print('=');
      break;
    case 0x3E:
      Serial.print('>');
      break;
    case 0x3F:
      Serial.print('?');
      break;
    case 0x40:
      Serial.print('@');
      break;
    case 0x41:
      Serial.print('A');
      break;
    case 0x42:
      Serial.print('B');
      break;
    case 0x43:
      Serial.print('C');
      break;
    case 0x44:
      Serial.print('D');
      break;
    case 0x45:
      Serial.print('E');
      break;
    case 0x46:
      Serial.print('F');
      break;
    case 0x47:
      Serial.print('G');
      break;
    case 0x48:
      Serial.print('H');
      break;
    case 0x49:
      Serial.print('I');
      break;
    case 0x4A:
      Serial.print('J');
      break;
    case 0x4B:
      Serial.print('K');
      break;
    case 0x4C:
      Serial.print('L');
      break;
    case 0x4D:
      Serial.print('M');
      break;
    case 0x4E:
      Serial.print('N');
      break;
    case 0x4F:
      Serial.print('O');
      break;
    case 0x50:
      Serial.print('P');
      break;
    case 0x51:
      Serial.print('Q');
      break;
    case 0x52:
      Serial.print('R');
      break;
    case 0x53:
      Serial.print('S');
      break;
    case 0x54:
      Serial.print('T');
      break;
    case 0x55:
      Serial.print('U');
      break;
    case 0x56:
      Serial.print('V');
      break;
    case 0x57:
      Serial.print('W');
      break;
    case 0x58:
      Serial.print('X');
      break;
    case 0x59:
      Serial.print('Y');
      break;
    case 0x5A:
      Serial.print('Z');
      break;
    case 0x5B:
      Serial.print('[');
      break;
    case 0x5C:
      Serial.print('\\');
      break;
    case 0x5D:
      Serial.print(']');
      break;
    case 0x5E:
      Serial.print('^');
      break;
    case 0x5F:
      Serial.print('_');
      break;
    case 0x60:
      Serial.print('`');
      break;
    // Other characters only printable on a 16-segment display
    case 0x61:
    case 0x62:
    case 0x63:
    case 0x64:
    case 0x65:
    case 0x66:
    case 0x67:
    case 0x68:
    case 0x69:
    case 0x6A:
    case 0x6B:
    case 0x6C:
    case 0x6D:
    case 0x6E:
    case 0x6F:
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x73:
    case 0x74:
    case 0x75:
    case 0x76:
    case 0x77:
    case 0x78:
    case 0x79:
    case 0x7A:
    case 0x7B:
    case 0x7C:
    case 0x7D:
    case 0x7E:
    case 0x7F:
    default:
      Serial.print('~');
      break;
  }
}
