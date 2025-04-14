import matplotlib.pyplot as plt
import numpy as np

def plot_hash_collisions(filename, output_image, style="ggplot"):
    hash_values = []
    collisions = []
    with open(filename, 'r') as f:
        for line_num, line in enumerate(f, 1):
            line = line.strip()
            parts = line.split()
                
            try:
                hash_val = int(parts[0])
                coll = int(parts[1])
                hash_values.append(hash_val)
                collisions.append(coll)
            except ValueError:
                print(f"Error: {line_num}")
                continue

    max_hash = max(hash_values)

    plt.style.use(style)
    fig, ax = plt.subplots(figsize=(12, 6))
        
    if len(hash_values) > 500:
        ax.hist(hash_values, weights=collisions, bins=50, color='skyblue', edgecolor='black')
    else:
        ax.bar(hash_values, collisions, width=1.0, color='skyblue', edgecolor='black')
    
    ax.set_title("Распределение коллизий хэш-функции", fontsize=14)
    ax.set_xlabel("Значение хэша", fontsize=12)
    ax.set_ylabel("Число коллизий", fontsize=12)
    ax.grid(axis='y', linestyle='--', alpha=0.7)
        
    ax.set_xticks([0, max_hash])
    ax.set_xticklabels(['0', str(max_hash)])
        
    total_collisions = sum(collisions)
    unique_hashes = len([c for c in collisions if c > 0])
    avg_collisions = total_collisions / unique_hashes if unique_hashes > 0 else 0
        
    metrics_text = f"Всего коллизий: {total_collisions}\nУникальных хэшей: {unique_hashes}\nСреднее: {avg_collisions:.2f}"
    ax.legend([metrics_text], loc='upper right', facecolor='white')
                
    plt.savefig(output_image, dpi=300, bbox_inches='tight')
    print(f"Saved in: {output_image}")

plot_hash_collisions("collisions.txt", output_image="collisions.png")