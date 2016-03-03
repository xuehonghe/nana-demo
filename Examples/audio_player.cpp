

#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/audio/player.hpp>
#include <nana/threads/pool.hpp>

int main()
{
#ifdef NANA_ENABLE_AUDIO

    nana::audio::player player("../Examples/audio1.wav");
    nana::threads::pool pool(1); //Only 1 thread.

    using namespace nana;

    form fm;
    button btn     (fm, nana::rectangle(10, 10, 180, 24));
    button btn_wait(fm, nana::rectangle(10, 40, 180, 24));
    btn     .caption("Play the audio");
    btn_wait.caption("Play and wait 5 min !!!!");

    btn.events().click(pool_push(pool, [&]()
                           {
                               player.play();
                           }));
    btn_wait.events().click([&]()
                       {
                         player.play();
                       });

    fm.show();

    exec(&fm,1,5,[&btn]()
	{
		click(btn);
	});
#endif	//NANA_ENABLE_AUDIO
}
