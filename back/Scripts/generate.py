import argparse
from diffusers import StableDiffusionPipeline
import torch
from PIL import Image
import os

def generate_image(prompt, filename, model_id):
    """
    Genera una imagen desde un prompt y la guarda en la carpeta 'generated/'.
    :param prompt: texto descriptivo.
    :param filename: nombre del archivo (sin ruta).
    :param model_id: modelo de Hugging Face.
    """

    # Asegurar que la carpeta exista
    output_dir = "generated"
    os.makedirs(output_dir, exist_ok=True)

    # Ruta completa (forzada a generated/)
    output_path = os.path.join(output_dir, filename)

    # Cargar modelo
    pipe = StableDiffusionPipeline.from_pretrained(
        model_id,
        torch_dtype=torch.float32
    ).to("cpu")

    # Generar imagen
    image = pipe(prompt).images[0]
    image.save(output_path)
    print(f"✅ Imagen guardada en {output_path}")

def main():
    parser = argparse.ArgumentParser(description="🎨 Generador de imágenes")
    parser.add_argument("--prompt", required=True, help="Texto descriptivo")
    parser.add_argument("--filename", default="output.png", help="Nombre del archivo")
    parser.add_argument("--model", default="CompVis/stable-diffusion-v1-4", help="Modelo Hugging Face")
    args = parser.parse_args()

    generate_image(args.prompt, args.filename, args.model)

if __name__ == "__main__":
    main()
