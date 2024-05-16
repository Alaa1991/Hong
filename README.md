# Hong Pro Music/Video/Audio Player

Hong Pro Music/Video/Audio Player is a versatile and powerful multimedia player written in C++. It supports a wide range of audio and video formats and offers robust features including high-quality playback and audio file conversion using FFmpeg.

## Features

- **Multi-Format Support**: Supports MP3, WAV, FLAC, AAC, MP4, AVI, MKV, and more.
- **High-Quality Playback**: Smooth and high-fidelity audio and video playback.
- **Audio Conversion**: Convert audio files between different formats with FFmpeg.
- **User-Friendly Interface**: Intuitive and easy-to-navigate interface.
- **Custom Playlists**: Create, manage, and save custom playlists.
- **Equalizer and Audio Effects**: Enhance sound quality with built-in equalizer and audio effects.
- **Subtitle Support**: Watch videos with subtitles in multiple formats.
- **Cross-Platform Compatibility**: Runs smoothly on Windows, macOS, and Linux.

## Prerequisites

- Git
- C++ Compiler
- FFmpeg library
- Git LFS (for handling large files)

## Installation

1. **Clone the Repository**:
    ```sh
    git clone https://github.com/Alaa1991/Hong.git
    cd Hong
    ```

2. **Install Dependencies**:
    - Install FFmpeg from [here](https://ffmpeg.org/download.html).
    - Install Git LFS from [here](https://git-lfs.github.com/).

3. **Build the Project**:
    - Follow the build instructions specific to your platform. For example, using a C++ compiler like `g++`:
    ```sh
    g++ -o HongPro *.cpp -lavformat -lavcodec -lavutil -lswresample -lswscale
    ```

## Usage

1. **Run the Application**:
    ```sh
    ./HongPro
    ```

2. **Add Media Files**:
    - Drag and drop your media files into the interface or use the file menu to add them.

3. **Play and Enjoy**:
    - Select your media file and press play. Use the features like playlists, equalizer, and audio effects to enhance your experience.

4. **Convert Audio Files**:
    - Access the audio conversion tool from the menu, choose the source file and desired output format, and convert with a single click.

## Contributing

We welcome contributions from the community. If you have suggestions, feature requests, or bug reports, please open an issue on GitHub. For code contributions, fork the repository, make your changes, and submit a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Developer Information

**Sole Developer**: Alaa Adil  
**Email**: alaa.adil.k@gmail.com  
**Phone**: +9647728237909
