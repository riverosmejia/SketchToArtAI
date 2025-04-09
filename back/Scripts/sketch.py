import argparse
from PIL import Image
from diffusers import StableDiffusionImg2ImgPipeline
import torch

def generate_from_sketch(sketch_path, prompt):
    # Cargar imagen del bosquejo
    init_image = Image.open(sketch_path).convert("RGB").resize((512, 512))

    # Selección del modelo automática (puedes ajustar si tienes varios modelos)
    model_id = "CompVis/stable-diffusion-v1-4"

    # Cargar el pipeline de imagen a imagen
    pipe = StableDiffusionImg2ImgPipeline.from_pretrained(model_id, torch_dtype=torch.float32).to("cpu")

    # Generar la imagen a partir del bosquejo y el prompt
    result = pipe(prompt=prompt, image=init_image, strength=0.75, guidance_scale=7.5).images[0]

    # Guardar la imagen
    output_path = "generated/generated_from_sketch.png"
    result.save(output_path)
    print(f"✅ Imagen generada y guardada en {output_path}")

def main():
    parser = argparse.ArgumentParser(description="🖌️ Generador desde bosquejo con Stable Diffusion")
    parser.add_argument("--sketch", required=True, help="Ruta al bosquejo (imagen base).")
    parser.add_argument("--prompt", required=True, help="Descripción textual de lo que se desea generar.")

    args = parser.parse_args()
    generate_from_sketch(args.sketch, args.prompt)

if __name__ == "__main__":
    main()