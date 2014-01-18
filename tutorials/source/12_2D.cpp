#include <iostream>
#include <cstdlib>
#include "yse.hpp"
#ifdef WINDOWS
#include <conio.h>
#else
#include "wincompat.h"
#endif

/* YSE doesn't really have '2D' sounds like most sound engines. Instead,
   you can make a sound's position relative to the listener object. This
   amounts to the same thing, but gives you extra flexibility like mapping 
   some gui sounds a bit more to the right or the left, according to the 
   gui element position.
*/

YSE::sound count, flies, kick;

int main() {
  YSE::System.init();
  count.create("countdown.ogg", NULL, true);
  flies.create("flies.ogg", NULL, true);
  kick.create("kick.ogg", NULL, true);

  std::cout << "Use keyboard to jump to a number." << std::endl;
  std::cout << "Use WASD to move the listener."    << std::endl;
  std::cout << "...or e to exit."                  << std::endl;

  // play mono sound in 2D space, but you can still alter it's position 
  // positions for a 2D sound will be relative to the listener position
  count.pan2D(true).play();

  // keep this sound in 2D space, but pan each channel as far as possible from the opposite channel
  // so for this stereo sound, spread is -90 degrees and 90 degrees
  // with spread 0.5, it would be at -45 and 45 degrees
  flies.pan2D(true).spread3D(1.0).play();


  // this sound is in 3D space, at initial listener position (0)
  kick.play();

  while (true) {
    if (_kbhit()) {
      char ch = _getch();
      YSE::Vec pos = YSE::Listener.pos();
      switch(ch) {
        case '0': count.time(11.2f * 44100).pos(YSE::Vec(-5, 0, 0)); break;
        case '1': count.time(10.0f * 44100).pos(YSE::Vec(-4, 0, 0)); break;
        case '2': count.time( 9.0f * 44100).pos(YSE::Vec(-3, 0, 0)); break;
        case '3': count.time( 8.0f * 44100).pos(YSE::Vec(-2, 0, 0)); break;
        case '4': count.time( 6.7f * 44100).pos(YSE::Vec(-1, 0, 0)); break;
        case '5': count.time( 5.5f * 44100).pos(YSE::Vec( 0, 0, 0)); break;
        case '6': count.time( 4.3f * 44100).pos(YSE::Vec( 1, 0, 0)); break;
        case '7': count.time( 3.2f * 44100).pos(YSE::Vec( 2, 0, 0)); break;
        case '8': count.time( 2.0f * 44100).pos(YSE::Vec( 3, 0, 0)); break;
        case '9': count.time( 1.0f * 44100).pos(YSE::Vec( 4, 0, 0)); break;
        
        // we can move the listener but it will only affect kick because other
        // sounds are in 2D space
        case 'w': pos.z += 0.1; YSE::Listener.pos(pos); break;
        case 's': pos.z -= 0.1; YSE::Listener.pos(pos); break;
        case 'a': pos.x -= 0.1; YSE::Listener.pos(pos); break;
        case 'd': pos.x += 0.1; YSE::Listener.pos(pos); break;

        case 'e': goto exit;
      }
    }

    YSE::System.sleep (100);
    YSE::System.update(   );
  }    

exit:
  YSE::System.close();
  return 0;
}
