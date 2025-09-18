import cv2
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, RadioButtons

def process_image(path, output_width=128, output_height=32, threshold=128,
                  blur=0, mode="binary", invert=False):
    # Kép betöltése szürkeárnyalatban
    img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)
    img = cv2.resize(img, (output_width, output_height), interpolation=cv2.INTER_LANCZOS4)

    # Gaussian blur, ha kell
    if blur > 0:
        k = blur if blur % 2 == 1 else blur + 1  # kernel méretnek páratlannak kell lennie
        img = cv2.GaussianBlur(img, (k, k), 0)

    # Feldolgozási mód
    if mode == "binary":
        _, img = cv2.threshold(img, threshold, 255, cv2.THRESH_BINARY)

    elif mode == "canny":
        img = cv2.Canny(img, threshold, threshold * 2)

    elif mode == "morph":
        edges = cv2.Canny(img, threshold, threshold * 2)
        kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (2, 2))
        img = cv2.morphologyEx(edges, cv2.MORPH_CLOSE, kernel)

    elif mode == "skeleton":
        edges = cv2.Canny(img, threshold, threshold * 2)
        try:
            from cv2.ximgproc import thinning
            img = thinning(edges)
        except ImportError:
            img = edges  # fallback, ha nincs ximgproc modul

    if invert:
        img = cv2.bitwise_not(img)

    return Image.fromarray(img)

def image_to_bitmap(img):
    pixels = img.load()
    width, height = img.size
    bitmap = []

    for page in range(height // 8):
        for x in range(width):
            byte = 0
            for bit in range(8):
                y = page * 8 + bit
                if pixels[x, y] == 0:
                    byte |= (1 << bit)
            bitmap.append(byte)

    return bitmap

def save_as_c_array(bitmap, varname="image_data"):
    out = f"const uint8_t {varname}[] = {{\n"
    for i, b in enumerate(bitmap):
        if i % 16 == 0:
            out += "    "
        out += f"0x{b:02X}, "
        if (i+1) % 16 == 0:
            out += "\n"
    out += "};\n"
    return out


if __name__ == "__main__":
    image_path = "260px-OP_C014_misato.jpg"
    threshold_init = 128
    blur_init = 0
    mode_init = "binary"

    img = process_image(image_path, threshold=threshold_init, blur=blur_init, mode=mode_init)

    # Plot + UI setup
    fig, ax = plt.subplots()
    plt.subplots_adjust(bottom=0.45)
    im_display = ax.imshow(img, cmap="gray", vmin=0, vmax=255)
    ax.set_title(f"OLED 128x32 preview - mode={mode_init}, th={threshold_init}, blur={blur_init}")
    ax.axis("off")

    # Threshold csúszka
    ax_slider_th = plt.axes([0.2, 0.25, 0.65, 0.03])
    slider_th = Slider(ax_slider_th, 'Threshold', 0, 255, valinit=threshold_init, valstep=1)

    # Blur csúszka
    ax_slider_blur = plt.axes([0.2, 0.18, 0.65, 0.03])
    slider_blur = Slider(ax_slider_blur, 'Blur', 0, 10, valinit=blur_init, valstep=1)

    # Módválasztó
    ax_radio = plt.axes([0.05, 0.05, 0.25, 0.25])
    radio = RadioButtons(ax_radio, ('binary', 'canny', 'morph', 'skeleton'), active=0)

    # Update callback
    def update(val=None):
        threshold = int(slider_th.val)
        blur = int(slider_blur.val)
        mode = radio.value_selected
        new_img = process_image(image_path, threshold=threshold, blur=blur, mode=mode)
        im_display.set_data(new_img)
        ax.set_title(f"OLED 128x32 preview - mode={mode}, th={threshold}, blur={blur}")
        fig.canvas.draw_idle()

    slider_th.on_changed(update)
    slider_blur.on_changed(update)
    radio.on_clicked(update)

    plt.show()

    # --- ha menteni akarod a bitmapot a kiválasztott beállításokkal ---
    # bmp = image_to_bitmap(img)
    # with open("bitmap.h", "w") as f:
    #     f.write(save_as_c_array(bmp, "myBitmap"))
