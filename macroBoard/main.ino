const HKEY_ALT_L = 0x01;
const HKEY_CTRL_L = 0x02;
const HKEY_SHIFT_L = 0x04;
const HKEY_ALT_R = 0x08;
const HKEY_CTRL_R = 0x10;
const HKEY_SHIFT_R = 0x20;

struct Hotkey {
  short modifiers;
}

struct Macro {
  Hotkey steps[];
  int delay;
}

void setup()
{
	
}

void loop()
{
	
}
