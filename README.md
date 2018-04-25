# Launch SSH

SSH launcher which saves a history of launched sessions which can be filtered through using auto completion and keyboard navigation the next time you want to launch a session.

## Usage

### Launch a new session
Run `launch_ssh` from the menu (or a global keyboard shortcut to be extra quick) and type which host you want to connect to.

Press `RETURN` to start the session in a new terminal.

This saves the session hostname in your history and will make it easy to start the next time.


### Navigate and autocomplete
When some history items are filled in, you can navigate quickly through them using the arrow and `RETURN` keys or by typing some letters and pressing `TAB` for auto completion.

### Delete old sessions
Delete records from your history you don't want using the `DELETE` key.

## Installing

### Ubuntu / Linux Mint

Download and install:

* [launch-ssh_0.1.2-bionic_amd64.deb](https://github.com/DemonTPx/launch-ssh/releases/download/0.1.2/launch-ssh_0.1.2-bionic_amd64.deb)
* [launch-ssh_0.1.2-xenial_amd64.deb](https://github.com/DemonTPx/launch-ssh/releases/download/0.1.2/launch-ssh_0.1.2-xenial_amd64.deb)

It is recommended that you add a global keyboard shortcut (eg. to `SUPER+Q`) which runs `launch_ssh` to easily launch SSH sessions using this application.

### From source (linux)

Install the following packages:

    libwxgtk3.0-dev wx3.0-headers libwxgtk3.0-0v5

Then run the following commands from the working copy:

    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release ../
    make -j 2
    mv launch_ssh /usr/local/bin/launch_ssh

## Credits

The `strnatcmp` code was written by Martin Pool and was taken from [Github](https://github.com/sourcefrog/natsort). 

The icon was taken from [moka-icon-theme](https://github.com/snwh/moka-icon-theme) by [Sam Hewitt](https://github.com/snwh) which is under a [Creative Commons Attribution ShareAlike 4.0](https://creativecommons.org/licenses/by-sa/4.0) license.

## License

The code is under MIT ([LICENSE](LICENSE)).

The `strnatcmp` code's license can be found in the [source](src/strnatcmp.c) and [header](src/strnatcmp.h) files itself.

The icon is under [Creative Commons Attribution ShareAlike 4.0](https://creativecommons.org/licenses/by-sa/4.0)
