# Launch SSH

SSH launcher which saves a history of launched sessions which can be filtered through the next time you want to launch a session.

## Installing

### Ubuntu / Linux Mint

Download and install:

* [launch-ssh_0.1-xenial_amd64.deb](https://github.com/DemonTPx/launch-ssh/releases/download/0.1/launch-ssh_0.1-xenial_amd64.deb)
* [launch-ssh_0.1-artful_amd64.deb](https://github.com/DemonTPx/launch-ssh/releases/download/0.1/launch-ssh_0.1-artful_amd64.deb)

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

The icon was taken from [moka-icon-theme](https://github.com/snwh/moka-icon-theme) by [Sam Hewitt](https://github.com/snwh) which is under a [Creative Commons Attribution ShareAlike 4.0](https://creativecommons.org/licenses/by-sa/4.0) license.

## License

The code is under MIT ([LICENSE](LICENSE)).

The icon is under [Creative Commons Attribution ShareAlike 4.0](https://creativecommons.org/licenses/by-sa/4.0)
