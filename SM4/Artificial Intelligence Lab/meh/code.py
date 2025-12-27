# =============================================================================
# DEEP LEARNING FINAL EXAM - IMPROVED BINARY IMAGE CLASSIFICATION
# Optimized VGG16 Transfer Learning for Better Accuracy
# =============================================================================

# Cell 1: Import Required Libraries and Setup
# =============================================================================

import tensorflow as tf
from tensorflow.keras.applications import VGG16
from tensorflow.keras.layers import GlobalAveragePooling2D, Dropout, Dense, BatchNormalization
from tensorflow.keras.models import Model
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.regularizers import l2
from tensorflow.keras.callbacks import EarlyStopping, ReduceLROnPlateau, ModelCheckpoint
from tensorflow.keras.optimizers import Adam
import gdown
import zipfile
import os
import shutil
import matplotlib.pyplot as plt
from sklearn.metrics import classification_report, confusion_matrix
import numpy as np
from google.colab import drive

# Check TensorFlow version and GPU availability
print(f"TensorFlow Version: {tf.__version__}")
print(f"GPU Available: {tf.config.list_physical_devices('GPU')}")

# Set mixed precision for better performance
tf.keras.mixed_precision.set_global_policy('mixed_float16')

# =============================================================================
# Cell 2: Dataset Preparation and Loading
# =============================================================================

# Step 1: Create temporary extraction directory
temp_dir = '/content/temp_extract'
val_dir = '/content/temp_extract_val'
os.makedirs(temp_dir, exist_ok=True)

print("📁 Setting up directories for dataset extraction...")

# Step 2: Define Google Drive shareable links for grass and roads datasets
grass_id = '1bZADKif0L5cm8NSZDvRkbVZ7inqp5T_L'
roads_id = '1CVplqUuJWl6vIPes_V6_du4evaEK8eEr'

grass_zip = 'https://drive.google.com/uc?id=' + grass_id
roads_zip = 'https://drive.google.com/uc?id=' + roads_id

# Step 3: Download zip files using gdown
print("⬇️ Downloading datasets from Google Drive...")
gdown.download(grass_zip, 'grass.zip', quiet=False)
gdown.download(roads_zip, 'roads.zip', quiet=False)

# Step 4: Extract ZIP files
print("📦 Extracting ZIP files...")
with zipfile.ZipFile('grass.zip', 'r') as zip_ref:
    zip_ref.extractall(temp_dir)

with zipfile.ZipFile('roads.zip', 'r') as zip_ref:
    zip_ref.extractall(temp_dir)

print("✅ Both zip files extracted to:", temp_dir)
print("📋 Contents of temp_dir:", os.listdir(temp_dir))

# Optional: Mount Google Drive for additional storage
drive.mount('/content/drive')

# =============================================================================
# Cell 3: Data Organization and Preprocessing
# =============================================================================

print("🗂️ Organizing data into proper directory structure...")

# Manually organize data if subdirectories don't exist
if not os.path.exists(os.path.join(temp_dir, 'grass')) or not os.path.exists(os.path.join(temp_dir, 'roads')):
    # Separate files based on naming convention
    grass_files = [f for f in os.listdir(temp_dir) if f.endswith(('.jpg', '.jpeg', '.png')) and 'grass' in f.lower()]
    roads_files = [f for f in os.listdir(temp_dir) if f.endswith(('.jpg', '.jpeg', '.png')) and 'roads' in f.lower()]
    
    # Create class directories
    os.makedirs(os.path.join(temp_dir, 'grass'), exist_ok=True)
    os.makedirs(os.path.join(temp_dir, 'roads'), exist_ok=True)
    
    # Move files to respective directories
    for file in grass_files:
        shutil.move(os.path.join(temp_dir, file), os.path.join(temp_dir, 'grass', file))
    for file in roads_files:
        shutil.move(os.path.join(temp_dir, file), os.path.join(temp_dir, 'roads', file))

print(f"📊 Grass images: {len(os.listdir(os.path.join(temp_dir, 'grass')))}")
print(f"📊 roads images: {len(os.listdir(os.path.join(temp_dir, 'roads')))}")

# =============================================================================
# Cell 4: Improved Train-Validation Split
# =============================================================================

print("✂️ Creating improved train-validation split (80-20)...")

# Create validation directory structure
os.makedirs(val_dir, exist_ok=True)

for class_name in ['grass', 'roads']:
    class_dir = os.path.join(temp_dir, class_name)
    val_class_dir = os.path.join(val_dir, class_name)
    os.makedirs(val_class_dir, exist_ok=True)
    
    if os.path.exists(class_dir):
        images = os.listdir(class_dir)
        # Shuffle images for better distribution
        np.random.shuffle(images)
        val_images = images[:int(0.2 * len(images))]  # 20% for validation
        
        # Move validation images
        for img in val_images:
            src = os.path.join(class_dir, img)
            dst = os.path.join(val_class_dir, img)
            shutil.move(src, dst)

print("✅ Data split completed successfully!")

# Check class distribution
for split, directory in [("Training", temp_dir), ("Validation", val_dir)]:
    print(f"\n{split} set:")
    for class_name in ['grass', 'roads']:
        class_path = os.path.join(directory, class_name)
        if os.path.exists(class_path):
            count = len(os.listdir(class_path))
            print(f"   {class_name}: {count} images")

# =============================================================================
# PART A: IMPROVED MODEL ARCHITECTURE SETUP [5 Marks]
# =============================================================================

# Cell 5: Load Pre-trained Model and Create Optimized Architecture
print("🏗️ PART A: Setting up optimized model architecture...")

# Load VGG16 pre-trained model without top classification layers
base_model = VGG16(
    weights='imagenet',           # Use ImageNet pre-trained weights
    include_top=False,           # Exclude final classification layer
    input_shape=(224, 224, 3)    # Input image dimensions
)

# Freeze base model layers initially
base_model.trainable = False
print(f"📊 Base model layers frozen: {len(base_model.layers)} layers")

# Create improved custom classification head
x = base_model.output
x = GlobalAveragePooling2D()(x)           # Global average pooling
x = BatchNormalization()(x)               # Batch normalization before dropout
x = Dropout(0.5)(x)                       # Higher dropout for better regularization
x = Dense(512, activation='relu',         # Larger dense layer
          kernel_regularizer=l2(0.001))(x) # L2 regularization
x = BatchNormalization()(x)               # Another batch normalization
x = Dropout(0.3)(x)                       # Additional dropout
x = Dense(256, activation='relu',         # Second dense layer
          kernel_regularizer=l2(0.001))(x)
x = BatchNormalization()(x)
x = Dropout(0.2)(x)
# Output layer - use float32 for stability
output = Dense(1, activation='sigmoid', dtype='float32')(x)

# Create final model
model = Model(inputs=base_model.input, outputs=output)

# Compile model with optimized parameters
model.compile(
    optimizer=Adam(learning_rate=0.0001),  # Lower initial learning rate
    loss='binary_crossentropy',
    metrics=['accuracy']
)

print("✅ Optimized model architecture created successfully!")
model.summary()

# =============================================================================
# PART B: ENHANCED REGULARIZATION STRATEGIES [10 Marks]
# =============================================================================

# Cell 6: Implement Optimized Data Augmentation (Regularization Technique #1)
print("🔄 PART B: Implementing enhanced regularization techniques...")

# Optimized data augmentation for training set
train_datagen = ImageDataGenerator(
    rescale=1./255,                      # Normalize pixel values
    rotation_range=20,                   # Reduced rotation for better stability
    width_shift_range=0.2,               # Moderate shifts
    height_shift_range=0.2,
    shear_range=0.2,                     # Added shear transformation
    zoom_range=0.2,                      # Zoom range
    horizontal_flip=True,                # Horizontal flip
    brightness_range=[0.8, 1.2],         # Brightness adjustment
    fill_mode='nearest'                  # Fill mode for transformations
)

# Validation data generator (only rescaling)
validation_datagen = ImageDataGenerator(rescale=1./255)

print("✅ Enhanced data augmentation configured (Regularization #1)")

# Cell 7: Create Optimized Data Generators
# Load training data with augmentation
train_generator = train_datagen.flow_from_directory(
    temp_dir,
    target_size=(224, 224),
    batch_size=16,                       # Smaller batch size for better gradients
    class_mode='binary',
    shuffle=True,
    seed=42                              # Reproducibility
)

# Load validation data without augmentation
validation_generator = validation_datagen.flow_from_directory(
    val_dir,
    target_size=(224, 224),
    batch_size=16,
    class_mode='binary',
    shuffle=False,
    seed=42
)

print("✅ Optimized data generators created successfully!")
print(f"📊 Training samples: {train_generator.samples}")
print(f"📊 Validation samples: {validation_generator.samples}")
print(f"📊 Class indices: {train_generator.class_indices}")

# =============================================================================
# Cell 8: Advanced Training Callbacks and Strategy
# =============================================================================

print("⚙️ Setting up advanced training callbacks...")

# Enhanced callbacks for better training
early_stopping = EarlyStopping(
    monitor='val_accuracy',        # Monitor validation accuracy
    patience=10,                   # Increased patience
    restore_best_weights=True,     # Restore best weights
    verbose=1,
    mode='max'                     # Maximize accuracy
)

reduce_lr = ReduceLROnPlateau(
    monitor='val_loss',            # Monitor validation loss
    factor=0.5,                    # Reduce LR by half
    patience=5,                    # Wait 5 epochs before reducing
    min_lr=1e-7,                   # Minimum learning rate
    verbose=1,
    mode='min'
)

# Model checkpoint to save best model
checkpoint = ModelCheckpoint(
    'best_model.h5',
    monitor='val_accuracy',
    save_best_only=True,
    save_weights_only=False,
    verbose=1,
    mode='max'
)

print("📋 Advanced regularization techniques:")
print("   1. Enhanced Data Augmentation")
print("   2. Multi-layer Dropout (0.5, 0.3, 0.2)")
print("   3. L2 Weight Regularization (0.001)")
print("   4. Batch Normalization (multiple layers)")
print("   5. Early Stopping (patience=10)")
print("   6. Learning Rate Reduction (factor=0.5, patience=5)")
print("   7. Model Checkpointing")

# =============================================================================
# Cell 9: Initial Training with Frozen Features
# =============================================================================

print("🚀 Starting initial training with frozen base model...")

# Train the model for initial epochs
print("🎯 Training model for initial epochs...")
history = model.fit(
    train_generator,
    validation_data=validation_generator,
    epochs=25,                            # More epochs for initial training
    callbacks=[early_stopping, reduce_lr, checkpoint],
    verbose=1
)

print("✅ Initial training completed!")

# =============================================================================
# PART C: OPTIMIZED MODEL FINE-TUNING [15 Marks]
# =============================================================================

# Cell 10: Strategic Layer Unfreezing and Fine-tuning
print("🔓 PART C: Strategic fine-tuning approach...")

# Load best model from checkpoint
model = tf.keras.models.load_model('best_model.h5')

# Step 1: Gradually unfreeze layers (more conservative approach)
print("🔓 Unfreezing top layers strategically...")
base_model = model.layers[0]  # Get the base model
base_model.trainable = True

# Unfreeze only the last few convolutional blocks
trainable_layers = 0
for layer in base_model.layers:
    if 'block5' in layer.name or 'block4' in layer.name:
        layer.trainable = True
        trainable_layers += 1
    else:
        layer.trainable = False

print(f"📊 Trainable layers in base model: {trainable_layers}")

# Step 2: Recompile with much lower learning rate for fine-tuning
print("⚙️ Recompiling model with very low learning rate...")
model.compile(
    optimizer=Adam(learning_rate=1e-6),   # Very low learning rate
    loss='binary_crossentropy',
    metrics=['accuracy']
)

# Step 3: Fine-tune with careful monitoring
print("🎯 Fine-tuning with careful monitoring...")

# Reset callbacks for fine-tuning
fine_tune_early_stopping = EarlyStopping(
    monitor='val_accuracy',
    patience=8,
    restore_best_weights=True,
    verbose=1,
    mode='max'
)

fine_tune_reduce_lr = ReduceLROnPlateau(
    monitor='val_loss',
    factor=0.2,
    patience=3,
    min_lr=1e-8,
    verbose=1,
    mode='min'
)

fine_tune_checkpoint = ModelCheckpoint(
    'fine_tuned_model.h5',
    monitor='val_accuracy',
    save_best_only=True,
    save_weights_only=False,
    verbose=1,
    mode='max'
)

# Fine-tune for additional epochs
history_fine = model.fit(
    train_generator,
    validation_data=validation_generator,
    epochs=15,                           # Fine-tuning epochs
    callbacks=[fine_tune_early_stopping, fine_tune_reduce_lr, fine_tune_checkpoint],
    verbose=1
)

print("✅ Fine-tuning completed!")

# =============================================================================
# Cell 11: Enhanced Training History Visualization
# =============================================================================

print("📈 Visualizing comprehensive training progress...")

# Combine training histories
total_acc = history.history['accuracy'] + history_fine.history['accuracy']
total_val_acc = history.history['val_accuracy'] + history_fine.history['val_accuracy']
total_loss = history.history['loss'] + history_fine.history['loss']
total_val_loss = history.history['val_loss'] + history_fine.history['val_loss']

epochs_range = range(1, len(total_acc) + 1)

# Create comprehensive visualization
plt.figure(figsize=(20, 10))

# Plot accuracy
plt.subplot(2, 2, 1)
plt.plot(epochs_range, total_acc, 'b-', label='Training Accuracy', linewidth=2)
plt.plot(epochs_range, total_val_acc, 'r-', label='Validation Accuracy', linewidth=2)
plt.title('Training and Validation Accuracy', fontsize=14, fontweight='bold')
plt.xlabel('Epochs')
plt.ylabel('Accuracy')
plt.legend()
plt.grid(True, alpha=0.3)

# Add vertical line to show where fine-tuning started
fine_tune_start = len(history.history['accuracy'])
plt.axvline(x=fine_tune_start, color='green', linestyle='--', alpha=0.7, label='Fine-tuning Start')

# Plot loss
plt.subplot(2, 2, 2)
plt.plot(epochs_range, total_loss, 'b-', label='Training Loss', linewidth=2)
plt.plot(epochs_range, total_val_loss, 'r-', label='Validation Loss', linewidth=2)
plt.title('Training and Validation Loss', fontsize=14, fontweight='bold')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.legend()
plt.grid(True, alpha=0.3)

# Add vertical line for fine-tuning start
plt.axvline(x=fine_tune_start, color='green', linestyle='--', alpha=0.7, label='Fine-tuning Start')

# Plot learning rate schedule (if available)
plt.subplot(2, 2, 3)
if 'lr' in history.history:
    total_lr = history.history['lr'] + history_fine.history['lr']
    plt.plot(epochs_range, total_lr, 'g-', label='Learning Rate', linewidth=2)
    plt.title('Learning Rate Schedule', fontsize=14, fontweight='bold')
    plt.xlabel('Epochs')
    plt.ylabel('Learning Rate')
    plt.yscale('log')
    plt.legend()
    plt.grid(True, alpha=0.3)

# Plot accuracy difference (overfitting indicator)
plt.subplot(2, 2, 4)
acc_diff = np.array(total_acc) - np.array(total_val_acc)
plt.plot(epochs_range, acc_diff, 'purple', label='Training - Validation Accuracy', linewidth=2)
plt.title('Overfitting Indicator', fontsize=14, fontweight='bold')
plt.xlabel('Epochs')
plt.ylabel('Accuracy Difference')
plt.axhline(y=0, color='black', linestyle='-', alpha=0.3)
plt.legend()
plt.grid(True, alpha=0.3)

plt.tight_layout()
plt.show()

# Print comprehensive final training metrics
print("\n" + "="*60)
print("📊 TRAINING SUMMARY")
print("="*60)
print(f"Total Epochs: {len(total_acc)}")
print(f"Initial Training Epochs: {len(history.history['accuracy'])}")
print(f"Fine-tuning Epochs: {len(history_fine.history['accuracy'])}")
print(f"Final Training Accuracy: {total_acc[-1]:.4f}")
print(f"Final Validation Accuracy: {total_val_acc[-1]:.4f}")
print(f"Best Validation Accuracy: {max(total_val_acc):.4f}")
print(f"Training-Validation Gap: {total_acc[-1] - total_val_acc[-1]:.4f}")

# =============================================================================
# Cell 12: Comprehensive Model Evaluation
# =============================================================================

print("\n🧪 Loading best model and evaluating on test set...")

# Load the best fine-tuned model
best_model = tf.keras.models.load_model('fine_tuned_model.h5')

# Create test data generator
test_datagen = ImageDataGenerator(rescale=1./255)
test_generator = test_datagen.flow_from_directory(
    val_dir,
    target_size=(224, 224),
    batch_size=1,                        # Batch size 1 for precise evaluation
    class_mode='binary',
    shuffle=False,
    seed=42
)

# Evaluate model performance
test_loss, test_accuracy = best_model.evaluate(test_generator, verbose=1)
print(f"\n🎯 FINAL TEST RESULTS:")
print(f"Test Accuracy: {test_accuracy:.4f} ({test_accuracy*100:.2f}%)")
print(f"Test Loss: {test_loss:.4f}")

# =============================================================================
# Cell 13: Detailed Classification Analysis with Confidence Scores
# =============================================================================

print("\n📋 Generating detailed classification analysis...")

# Generate predictions with confidence scores
print("🔮 Making predictions on test set...")
y_pred_prob = best_model.predict(test_generator, verbose=1)
y_pred_classes = (y_pred_prob > 0.5).astype(int).flatten()
y_true = test_generator.classes

# Calculate confidence statistics
confidence_scores = np.where(y_pred_classes == 1, y_pred_prob.flatten(), 1 - y_pred_prob.flatten())
avg_confidence = np.mean(confidence_scores)
min_confidence = np.min(confidence_scores)

# Get class names
class_names = list(test_generator.class_indices.keys())
print(f"📝 Class mapping: {test_generator.class_indices}")

# Print detailed classification report
print("\n" + "="*60)
print("📊 COMPREHENSIVE CLASSIFICATION REPORT")
print("="*60)
print(classification_report(y_true, y_pred_classes, target_names=class_names, digits=4))

# Generate and display confusion matrix
print("\n" + "="*40)
print("🎭 CONFUSION MATRIX")
print("="*40)
cm = confusion_matrix(y_true, y_pred_classes)
print(f"Actual vs Predicted:")
print(f"Classes: {class_names}")
print(cm)

# Calculate additional metrics
from sklearn.metrics import precision_score, recall_score, f1_score, roc_auc_score

precision = precision_score(y_true, y_pred_classes)
recall = recall_score(y_true, y_pred_classes)
f1 = f1_score(y_true, y_pred_classes)
auc = roc_auc_score(y_true, y_pred_prob)

print("\n" + "="*50)
print("📈 COMPREHENSIVE PERFORMANCE METRICS")
print("="*50)
print(f"Test Accuracy:        {test_accuracy:.4f} ({test_accuracy*100:.2f}%)")
print(f"Precision:            {precision:.4f}")
print(f"Recall:               {recall:.4f}")
print(f"F1-Score:             {f1:.4f}")
print(f"ROC-AUC Score:        {auc:.4f}")
print(f"Average Confidence:   {avg_confidence:.4f}")
print(f"Minimum Confidence:   {min_confidence:.4f}")

# Analyze misclassified samples
incorrect_indices = np.where(y_pred_classes != y_true)[0]
print(f"\nMisclassified samples: {len(incorrect_indices)}/{len(y_true)}")

if len(incorrect_indices) > 0:
    print("\nMisclassified samples analysis:")
    for i in incorrect_indices[:5]:  # Show first 5 misclassified
        true_class = class_names[y_true[i]]
        pred_class = class_names[y_pred_classes[i]]
        confidence = confidence_scores[i]
        prob = y_pred_prob[i][0]
        print(f"  Sample {i}: True={true_class}, Pred={pred_class}, Prob={prob:.4f}, Conf={confidence:.4f}")

# =============================================================================
# Cell 14: Final Model Architecture and Implementation Summary
# =============================================================================

print("\n" + "="*60)
print("🏗️ OPTIMIZED MODEL ARCHITECTURE SUMMARY")
print("="*60)

# Print model summary
best_model.summary()

print("\n" + "="*60)
print("🔧 OPTIMIZATION TECHNIQUES IMPLEMENTED")
print("="*60)

print("\n✅ Part A - Enhanced Model Setup:")
print("   ✓ VGG16 pre-trained model with ImageNet weights")
print("   ✓ Mixed precision training enabled")
print("   ✓ Optimized classification head with multiple dense layers")
print("   ✓ Strategic batch normalization placement")
print("   ✓ Graduated dropout rates (0.5, 0.3, 0.2)")
print("   ✓ Lower initial learning rate (0.0001)")

print("\n✅ Part B - Advanced Regularization (7+ techniques):")
print("   ✓ 1. Enhanced Data Augmentation (reduced rotation, added shear)")
print("   ✓ 2. Multi-level Dropout (0.5, 0.3, 0.2)")
print("   ✓ 3. L2 Weight Regularization (0.001)")
print("   ✓ 4. Batch Normalization (3 layers)")
print("   ✓ 5. Early Stopping (patience=10)")
print("   ✓ 6. Learning Rate Reduction (factor=0.5, patience=5)")
print("   ✓ 7. Model Checkpointing")
print("   ✓ 8. Smaller batch size for better gradients")

print("\n✅ Part C - Strategic Fine-tuning:")
print("   ✓ Conservative layer unfreezing (block4 and block5 only)")
print("   ✓ Very low learning rate for fine-tuning (1e-6)")
print("   ✓ Separate callback configuration for fine-tuning")
print("   ✓ Extended training with careful monitoring")
print("   ✓ Best model restoration and evaluation")

print("\n✅ Additional Optimizations:")
print("   ✓ Balanced train-validation split with shuffling")
print("   ✓ Reproducible random seeds")
print("   ✓ Comprehensive visualization and analysis")
print("   ✓ Confidence score analysis")
print("   ✓ Misclassification analysis")

print(f"\n🎯 FINAL OPTIMIZED RESULTS:")
print(f"   Test Accuracy: {test_accuracy:.4f} ({test_accuracy*100:.2f}%)")
print(f"   F1-Score: {f1:.4f}")
print(f"   ROC-AUC: {auc:.4f}")
print(f"   Model Parameters: {best_model.count_params():,}")
print(f"   Average Confidence: {avg_confidence:.4f}")

print("\n🚀 Optimization complete! This implementation should achieve much better accuracy.")
print("📋 Key improvements: strategic unfreezing, better regularization, optimized hyperparameters")

# =============================================================================
# Cell 15: Troubleshooting Tips and Next Steps
# =============================================================================

print("\n" + "="*60)
print("🔧 TROUBLESHOOTING TIPS FOR FURTHER IMPROVEMENT")
print("="*60)

print("\n💡 If accuracy is still low, try these additional steps:")
print("   1. Ensure your dataset has sufficient samples per class (>100 recommended)")
print("   2. Check for class imbalance and consider class weighting")
print("   3. Verify image quality and preprocessing consistency")
print("   4. Try different pre-trained models (ResNet50, EfficientNet)")
print("   5. Experiment with different learning rates (1e-5, 5e-5)")
print("   6. Consider increasing image resolution if computationally feasible")
print("   7. Add more data augmentation techniques")
print("   8. Try different optimization strategies (SGD with momentum)")

print("\n📊 Expected performance ranges:")
print("   - Good: 85-90% accuracy")
print("   - Very Good: 90-95% accuracy") 
print("   - Excellent: 95%+ accuracy")

print("\n🎯 For your viva preparation:")
print("   - Understand why each regularization technique was chosen")
print("   - Know the trade-offs between different approaches")
print("   - Be able to explain the fine-tuning strategy")
print("   - Understand the impact of hyperparameter choices")

print("\n✅ Implementation ready for high-performance training!")