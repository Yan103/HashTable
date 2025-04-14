import random

def sample_and_shuffle_words(file1, file2, output_file, sample_size=5000000):
    with open(file1, 'r') as f:
        words1 = [line.strip() for line in f if line.strip()]
    
    with open(file2, 'r') as f:
        words2 = [line.strip() for line in f if line.strip()]
    
    sampled_words1 = random.choices(words1, k=sample_size)
    sampled_words2 = random.choices(words2, k=sample_size)
    
    combined_words = sampled_words1 + sampled_words2
    random.shuffle(combined_words)
    
    with open(output_file, 'w') as f:
        for word in combined_words:
            f.write(word + '\n')

file1       = 'LOR_converted.txt' 
file2       = 'words.txt' 
output_file = 'mixed_test.txt'

sample_and_shuffle_words(file1, file2, output_file)
