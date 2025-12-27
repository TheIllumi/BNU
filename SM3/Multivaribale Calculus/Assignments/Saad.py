import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(-3, 3, 100)
y = np.linspace(-3, 3, 100)
X, Y = np.meshgrid(x, y)

Z = np.sqrt(((x**2)-4)*((Y**2)-9))

fig = plt.figure(figsize=(12, 6))

ax1 = fig.add_subplot(121, projection='3d')
ax1.plot_surface(X, Y, Z, cmap='viridis', edgecolor='k', alpha=0.7)
ax1.set_title("Surface Plot of $f(x, y)$")
ax1.set_xlabel("x")
ax1.set_ylabel("y")
ax1.set_zlabel("z")

ax2 = fig.add_subplot(122)
contour = ax2.contour(X, Y, Z, levels=10, cmap='viridis')
ax2.clabel(contour, inline= False, fontsize=8)
ax2.set_title("Level Curves of $f(x, y)$")
ax2.set_xlabel("x")
ax2.set_ylabel("y")

plt.tight_layout()
plt.show()