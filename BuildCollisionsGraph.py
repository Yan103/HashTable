import matplotlib.pyplot as plt
from numpy import var
import os

def plot_hash_collisions(filename, output_image, style="ggplot"):
    hash_values = []
    collisions = []
    total_collisions = 0  

    with open(filename, 'r') as f:
        for line_num, line in enumerate(f, 1):
            line = line.strip()
            parts = line.split()
                
            try:
                hash_val = int(parts[0])
                coll = int(parts[1])
                hash_values.append(hash_val)
                collisions.append(coll)
                total_collisions += coll  
            except ValueError:
                print(f"Ошибка в строке {line_num}: {line}")
                continue

    max_hash = max(hash_values) if hash_values else 0

    plt.style.use(style)
    fig, ax = plt.subplots(figsize=(12, 6))
        
    if len(hash_values) > 500:
        ax.hist(hash_values, weights=collisions, bins=50, color='skyblue', edgecolor='black')
    else:
        ax.bar(hash_values, collisions, width=1.0, color='skyblue', edgecolor='black')
    
    func_name = os.path.splitext(os.path.basename(filename))[0]
    ax.set_title(f"Распределение коллизий хэш-функции ({func_name})", fontsize=14)
    ax.set_xlabel("Значение хэша", fontsize=12)
    ax.set_ylabel("Число коллизий", fontsize=12)
    ax.grid(axis='y', linestyle='--', alpha=0.7)
        
    if max_hash > 0:
        ax.set_xticks([0, max_hash])
        ax.set_xticklabels(['0', str(max_hash)])
        
    unique_hashes = len([c for c in collisions if c > 0])
    avg_collisions = total_collisions / unique_hashes if unique_hashes > 0 else 0
    
    variance = var(collisions) if collisions else 0
        
    metrics_text = f"Уникальных хэшей: {unique_hashes}\nСреднее коллизий: {avg_collisions:.2f}\n σ: {variance:.2f}"
    
    ax.legend([metrics_text], loc='upper right', facecolor='white', handlelength=0)
                
    plt.savefig(output_image, dpi=300, bbox_inches='tight')
    print(f"Saved in: {output_image}")

plot_hash_collisions("results/ASCIIsum.txt", output_image="ASCIIsum.png")

