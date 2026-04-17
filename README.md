# 🖐️ Detección de Manos con OpenCV + MediaPipe → Arduino

![Python](https://img.shields.io/badge/Python-3.10-blue?logo=python&logoColor=white)
![OpenCV](https://img.shields.io/badge/OpenCV-4.x-green?logo=opencv)
![MediaPipe](https://img.shields.io/badge/MediaPipe-0.10-orange)
![Arduino](https://img.shields.io/badge/Arduino-Compatible-teal?logo=arduino)
![License](https://img.shields.io/badge/License-MIT-yellow)

Sistema de visión por computadora que detecta y cuenta los dedos de la mano en tiempo real usando la camara del pc, y envío de datos por puerto serie a un Arduino para controlar hardware externo.

---

## 📋 Tabla de Contenidos

- [Demo](#-demo)
- [¿Cómo funciona?](#-cómo-funciona)
- [Requisitos](#-requisitos)
- [Instalación](#-instalación)
- [Configuración](#️-configuración)
- [Uso](#-uso)
- [Estructura del proyecto](#-estructura-del-proyecto)
- [Comunicación con Arduino](#-comunicación-con-arduino)
- [Solución de problemas](#-solución-de-problemas)

---

## 🎬 Demo

El sistema detecta en tiempo real qué dedos están extendidos y muestra:

- El **conteo total** de dedos levantados (esquina superior izquierda)
- El **estado individual** de cada dedo (Pulgar, Índice, Medio, Anular, Meñique)
- El **esqueleto de la mano** superpuesto sobre la imagen de la cámara

---

## 🧠 ¿Cómo funciona?

### Detección del Pulgar
Se calculan los tres puntos clave del pulgar (`landmarks` 1, 2 y 4) y se obtiene el ángulo entre ellos usando la **Ley de Cosenos**. Si el ángulo supera los **150°**, el pulgar se considera extendido.

### Detección del resto de dedos (Índice, Medio, Anular, Meñique)
1. Se calcula el **centroide de la palma** a partir de 7 puntos de referencia.
2. Se mide la distancia del centroide a la **punta** de cada dedo y a su **base**.
3. Si la punta está más lejos del centroide que la base → el dedo está **extendido**.

### Envío a Arduino
Cuando el pulgar está levantado, se envía el carácter `'a'` por puerto serie; si está cerrado, se envía `'b'`. Esto puede extenderse fácilmente para enviar el conteo completo de dedos.

---

## 📦 Requisitos

### Software
| Paquete | Versión recomendada |
|---|---|
| Python | 3.10 |
| OpenCV | `opencv-contrib-python` 4.x |
| MediaPipe | 0.10.9 |
| NumPy | 1.23+ |
| PySerial | 3.5+ |

### Hardware
- Camara (integrada o USB)
- Arduino (Uno, Mega, Nano, etc.)
- Cable USB para conexión Arduino ↔ PC

---

## 🚀 Instalación

### 1. Clona el repositorio
```bash
git clone https://github.com/EzPlays/OpenCV-deteccion-de-manos-con-MediaPipe-y-envio-de-datos-a-Arduino.git
cd OpenCV-deteccion-de-manos-con-MediaPipe-y-envio-de-datos-a-Arduino
```

### 2. Crea un entorno virtual (recomendado)
```bash
python -m venv venv

# Windows
venv\Scripts\activate

# Linux / macOS
source venv/bin/activate
```

### 3. Instala las dependencias
```bash
pip install -r requirements.txt
```

---

## ⚙️ Configuración

Antes de ejecutar el script, ajusta estos parámetros según tu entorno:

```python
# Puerto serie donde está conectado tu Arduino
ser = serial.Serial('COM4', 9600, timeout=1)
#                    ^^^^
# Windows: 'COM3', 'COM4', etc.
# Linux:   '/dev/ttyUSB0' o '/dev/ttyACM0'
# macOS:   '/dev/cu.usbmodem...'

# Índice de la cámara (0 = cámara por defecto)
cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)
#                      ^
# Cambia a 1, 2... si tienes varias cámaras
```

Para encontrar el puerto correcto en Windows: **Administrador de dispositivos → Puertos (COM y LPT)**.

---

## ▶️ Uso

```bash
python main.py
```

- Muestra la ventana de la cámara con la detección en tiempo real.
- Presiona **`ESC`** para salir.

---

## 📁 Estructura del proyecto

```
📦 OpenCV-deteccion-de-manos/
 ┣ 📁 venv                      # Entorno virtual
 ┣ 📄 .gitignore                # Archivo de git
 ┣ 📄 accionamiento_leds.ino    # Script con el codigo para el Arduino
 ┣ 📄 LICENSE                   
 ┣ 📄 main.py                   # Script principal
 ┣ 📄 README.md                 # Este archivo
 ┗ 📄 requirements.txt          # Archivo con las versiones necesarias de las librerias
```

---

## 🔌 Comunicación con Arduino

El script envía datos por puerto serie que el Arduino puede leer con `Serial.read()`.

| Estado del pulgar | Byte enviado |
|---|---|
| Extendido ✋ | `'a'` |
| Cerrado ✊ | `'b'` |

### Ejemplo de código Arduino

```cpp
char dato;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT); // LED integrado
}

void loop() {
  if (Serial.available() > 0) {
    dato = Serial.read();
    if (dato == 'a') {
      digitalWrite(13, HIGH); // Enciende LED si el pulgar está levantado
    } else if (dato == 'b') {
      digitalWrite(13, LOW);  // Apaga LED si el pulgar está cerrado
    }
  }
}
```

---

## 🛠️ Solución de problemas

| Error | Causa | Solución |
|---|---|---|
| `ValueError: math domain error` | Precisión de punto flotante en `acos()` | Clampear el valor: `np.clip(cos_angle, -1.0, 1.0)` |
| `serial.SerialException` | Puerto COM incorrecto o Arduino desconectado | Verificar el puerto en el Administrador de dispositivos |
| Cámara no detectada | Índice de cámara incorrecto | Cambiar `VideoCapture(0)` por `VideoCapture(1)` |
| Detección inestable | Poca luz o fondo con mucho ruido | Mejorar iluminación y usar fondo neutro |
| `ModuleNotFoundError` | Dependencias no instaladas | Ejecutar `pip install -r requirements.txt` |

---

## 🤝 Contribuciones

¡Las contribuciones son bienvenidas! Si quieres mejorar el proyecto:

1. Haz un **fork** del repositorio
2. Crea una rama: `git checkout -b feature/mi-mejora`
3. Commitea tus cambios: `git commit -m 'feat: agrego mi mejora'`
4. Haz push: `git push origin feature/mi-mejora`
5. Abre un **Pull Request**

---

## 📄 Licencia

Este proyecto está bajo la licencia **MIT**. Consulta el archivo `LICENSE` para más detalles.



## Referencias

[Cómo instalar OpenCV en Windows? | Minicurso OpenCV – Parte 3](https://omes-va.com/como-instalar-opencv-en-windows/)

[? Como instalar MEDIAPIPE | Python](https://omes-va.com/como-instalar-mediapipe-python/)

[Capturar, guardar y leer un video en OpenCV y Python](https://omes-va.com/basicvideo/)

[Como usar MEDIAPIPE HANDS ?️ | Python – MediaPipe – OpenCV](https://omes-va.com/mediapipe-hands-python/)

[✌️ Contando dedos con visión artificial | Mediapipe – OpenCV – Python](https://omes-va.com/contando-dedos-mediapipe-opencv-python/)

[Comunicación PYTHON – ARDUINO con Pyserial | Mediapipe – OpenCV](https://omes-va.com/comunicacion-python-arduino-pyserial-mediapipe-opencv/)
