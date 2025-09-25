
# OpenGL Watch Model

---
---

## Highlights

- Modular C++ model components: body, band, hour/minute hands, screws, markers, buttons, pivot, etc.
- Simple animation subsystem for clock movement and interactions.
- GLSL vertex and fragment shaders for basic lighting and materials.
- Easy-to-follow project layout suitable for study, modification, and extension.
- Includes documentation screenshots and animated GIFs in `/docs`.

---

## Repo layout

```
.
├── animation/            # animation controller for the watch
├── constants/            # project-wide constants
├── docs/                 # screenshots + animated GIF previews
├── include/              # GLAD + KHR headers
├── models/               # individual model components (watch_body, band, screws...)
├── shaders/              # vertex + fragment GLSL shaders
├── utils/                # camera and helper utilities
├── main.cpp              # application entrypoint
├── glad.c                # GLAD loader (single-file)
└── README.md
```

Refer to the `models/` directory for component-level design: each element has its `.cpp` and `.h` pair for encapsulation.

---

### Run

Run this project with

```bash
g++ main.cpp glad.c models/watch_body.cpp models/watch_face.cpp models/watch_holder.cpp models/watch_band.cpp models/watch_hour.cpp models/watch_minute.cpp models/watch_pivot.cpp models/watch_screw.cpp models/watch_miniscrew.cpp models/watch_hourmarker.cpp models/watch_bighourmarker.cpp models/watch_button.cpp models/watch_lock.cpp animation/watch_animation.cpp -o watch -Iinclude -Iconstants -Imodels -Ianimation -lglfw -ldl -lGL && ./watch 

```

---
## Screenshots


![Right](https://github.com/im-w/OpenGl_Watch_Model/blob/main/docs/3.gif)

![Right](https://github.com/im-w/OpenGl_Watch_Model/blob/main/docs/4.gif)

![Left](https://github.com/im-w/OpenGl_Watch_Model/blob/main/docs/1.gif)

![Left](https://github.com/im-w/OpenGl_Watch_Model/blob/main/docs/2.gif)


    
