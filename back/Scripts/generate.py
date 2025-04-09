# generate.py

# argparse: permite definir y parsear argumentos desde la línea de comandos.
import argparse

# StableDiffusionPipeline: pipeline de Hugging Face para convertir texto en imagen.
from diffusers import StableDiffusionPipeline

# torch: la librería de PyTorch, usada por diffusers para manejar tensores y modelos.
import torch

# PIL.Image: parte de Pillow, útil para abrir, manipular y guardar imágenes.
from PIL import Image

def generate_image(prompt, output_path, model_id):
    """
    Carga el modelo y genera una imagen a partir de un prompt.
    :param prompt: Texto descriptivo de la imagen a generar.
    :param output_path: Ruta donde se guardará la imagen resultante.
    :param model_id: Identificador del modelo en Hugging Face Hub.
    """

    # from_pretrained: descarga (o usa caché) el modelo especificado.
    # torch_dtype=torch.float32: usamos precisión estándar, ideal para CPU.
    pipe = StableDiffusionPipeline.from_pretrained(
        model_id,
        torch_dtype=torch.float32
    ).to("cpu")  # .to("cpu") fuerza la ejecución en CPU.

    # Ejecuta el pipeline: pasa el prompt y recibe una lista de imágenes.
    image = pipe(prompt).images[0]

    # Guarda la primera imagen generada en disco.
    image.save(output_path)
    print(f"✅ Imagen guardada en {output_path}")

def main():
    """
    Función principal que parsea argumentos y llama a generate_image.
    """

    # Crea el parser de argumentos con descripción del script.
    parser = argparse.ArgumentParser(
        description="🎨 Generador de imágenes con Stable Diffusion"
    )

    # --prompt: texto obligatorio que describe la imagen.
    parser.add_argument(
        "--prompt",
        required=True,
        help="Texto que describe la imagen a generar."
    )

    # --output: ruta de salida, por defecto "output.png".
    parser.add_argument(
        "--output",
        default="output.png",
        help="Ruta de salida (por defecto: output.png)."
    )

    # --model: ID del modelo en HF Hub, por defecto SD v1-4.
    parser.add_argument(
        "--model",
        default="CompVis/stable-diffusion-v1-4",
        help="ID del modelo Hugging Face a usar."
    )

    # Parsea los argumentos y los guarda en args.
    args = parser.parse_args()

    # Llama a la función de generación con los valores proporcionados.
    generate_image(args.prompt, args.output, args.model)

# Este bloque asegura que main() solo se ejecute si corremos el script directamente.
if __name__ == "__main__":
    main()
