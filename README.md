



<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->



<!-- PROJECT LOGO -->
<br />
<div align="center">

<h3 align="center">RayLibGame</h3>

  <p align="center">
    A little project using raylib to learn and play around with game development
    <br />
    <br />
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#roadmap">Roadmap</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project
### Showcase Video

[GameVideo][game-video]

The idea for this project is to build a game that utilizes rocket jumping as a game mechanic to build a arcade shooter like doom or ultrakill.
Development is still on-going with implementation of a ECS(Entity Component System) as well, but i still have much to learn XD.




### Built With

* [![C++][C++]][C++-url]
* [![Raylib][Raylib]][Raylib-url]




<!-- GETTING STARTED -->
## Getting Started

For this project, I made it primarily on my daily macbook so the installation and usage are based off running it on macos

### Prerequisites
#### Installing Raylib
1. Go and install Raylib from this [release](https://github.com/raysan5/raylib/releases/tag/5.5)
2. Unzip and `cd` into that folder
3. Follow this guide on installing it, [guide for mac here](https://github.com/raysan5/raylib/wiki/Working-on-macOS)
4. Then after generating the `libraylib.a` file, take note where is it as you'll need to replace the one already in the repo with it

#### Make
you also have to install make to build the project, on mac you can just (if you have brew installed)
```sh
brew install make
```

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/lewislee42/RayLibGame.git
   ```
2. `cd` into the cloned directory
   ```sh
   cd RayLibGame
   ```
3. Replace the libraylib.a in the repo with the newly generated one
   ```sh
   rm -f ./lib/libraylib.a
   cp [the libraylib.a that you've generated] ./lib/libraylib.a
   ```
4. Run make to build the project
   ```sh
   make
   ```
5. Then you are done, you can run `./RayLibGame` in your console to run the game
   ```sh
   ./RaylibGame
   ```






<!-- ROADMAP -->
## Roadmap

- [x] Moving Player
- [x] Collision Detection
- [x] Spawning "Bullets"
- [ ] Implement ECS (entt)(Ongoing in `Integrating-ECS` branch)








<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/github_username/repo_name.svg?style=for-the-badge
[contributors-url]: https://github.com/github_username/repo_name/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/github_username/repo_name.svg?style=for-the-badge
[forks-url]: https://github.com/github_username/repo_name/network/members
[stars-shield]: https://img.shields.io/github/stars/github_username/repo_name.svg?style=for-the-badge
[stars-url]: https://github.com/github_username/repo_name/stargazers
[issues-shield]: https://img.shields.io/github/issues/github_username/repo_name.svg?style=for-the-badge
[issues-url]: https://github.com/github_username/repo_name/issues
[license-shield]: https://img.shields.io/github/license/github_username/repo_name.svg?style=for-the-badge
[license-url]: https://github.com/github_username/repo_name/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/linkedin_username
[game-video]: https://github.com/user-attachments/assets/37920c99-0dc6-46ef-8a68-8e5f40b20d4a
[C++]: https://img.shields.io/badge/C++-%2300599C.svg?logo=c%2B%2B&logoColor=white
[C++-url]: #
[RayLib]: https://img.shields.io/badge/RAYLIB-FFFFFF?style=for-the-badge&logo=raylib&logoColor=black
[Raylib-url]: https://www.raylib.com



