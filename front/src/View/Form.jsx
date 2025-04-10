import { useState } from 'react';
import styles from './ImageGeneratorUI.module.css';

export default function ImageGeneratorUI() {
  const [mode, setMode] = useState('prompt');
  const [prompt, setPrompt] = useState('');
  const [sketch, setSketch] = useState(null);
  const [resolution, setResolution] = useState('512x512');
  const [style, setStyle] = useState('realistic');

  const handleFileChange = (e) => {
    setSketch(e.target.files[0]);
  };

  const handleGenerate = () => {
    console.log({ prompt, sketch, resolution, style });
  };

  return (
    <div className={styles.container}>
      <div className={styles.wrapper}>
        <h1 className={styles.title}>SketchToArtAI – Generador de Imágenes</h1>

        <div className={styles.section}>
          <label className={styles.label}>Modo de Generación</label>
          <div className={styles.tabs}>
            <button
              className={`${styles.tabButton} ${mode === 'prompt' ? styles.active : ''}`}
              onClick={() => setMode('prompt')}
            >
              Solo Prompt
            </button>
            <button
              className={`${styles.tabButton} ${mode === 'sketch' ? styles.active : ''}`}
              onClick={() => setMode('sketch')}
            >
              Sketch + Prompt
            </button>
          </div>
        </div>

        <div className={styles.section}>
          <label className={styles.label}>Prompt</label>
          <textarea
            className={styles.textarea}
            value={prompt}
            onChange={(e) => setPrompt(e.target.value)}
            placeholder="Un castillo flotando sobre una isla mágica al atardecer..."
          />
        </div>

        {mode === 'sketch' && (
          <div className={styles.section}>
            <label className={styles.label}>Sube tu Sketch</label>
            <input
              type="file"
              accept="image/*"
              onChange={handleFileChange}
              className={styles.inputFile}
            />
          </div>
        )}

        <div className={styles.grid}>
          <div className={styles.gridItem}>
            <label className={styles.label}>Estilo Artístico</label>
            <select
              className={styles.select}
              value={style}
              onChange={(e) => setStyle(e.target.value)}
            >
              <option value="realistic">Realista</option>
              <option value="anime">Anime</option>
              <option value="digital">Pintura Digital</option>
              <option value="3d">3D</option>
            </select>
          </div>
        </div>

        <button onClick={handleGenerate} className={styles.generateButton}>
          🚀 Generar Imagen
        </button>

        <div className={styles.preview}>
          🖼️ La imagen generada se mostrará aquí
        </div>
      </div>
    </div>
  );
}
