# Assignment 3: Kubernetes Orchestration & Full DevOps Pipeline
## Complete Step-by-Step Guide with Screenshot Instructions

**Course:** DevOps and Cloud Computing Foundation | **Marks:** 100 | **Due:** Jun 3, 11:59 PM  
**Submission:** `.ova` VM snapshot uploaded to Google Drive (shareable link) + PDF Report via GCR

> 📌 **Submission note from professor:** Do NOT upload `.ova` directly to LMS. Upload to your Google Drive, set sharing to "Anyone with the link can edit", then submit that link on GCR.

---

## PART A GUIDE — Git & Version Control (10 marks)

> ✅ You said Part A is already done. Skip to **Recovery Screenshots** below.

---

### A — Recovery Screenshot Steps

Run these commands now to capture all missing proof for Part A.

**Where to run:** Ubuntu VM terminal

```bash
# 1. Show Git identity config
git config --list | grep user

# 2. Show all branches (local + remote)
git branch -a

# 3. Show commit history (last 15)
git log --oneline -15

# 4. Show .gitignore exists and its contents
cat ~/assignment3/.gitignore
```

---

📸 **SCREENSHOT 1 — Git Config**
- **When:** After running `git config --list | grep user`
- **What to show:** Lines showing `user.name` and `user.email`
- **Why:** Proves Git identity is configured
- **Save as:** `part-a-git-config.png`

---

📸 **SCREENSHOT 2 — Git Branches**
- **When:** After running `git branch -a`
- **What to show:** At least 3 branches: `main`, `develop`, and at least one `feature/` branch
- **Why:** Proves branching strategy (worth 3 marks)
- **Save as:** `part-a-git-branches.png`

---

📸 **SCREENSHOT 3 — Git Log**
- **When:** After running `git log --oneline -15`
- **What to show:** 10+ commits with descriptive messages
- **Why:** Proves meaningful commit history (worth 3 marks)
- **Save as:** `part-a-git-log.png`

---

📸 **SCREENSHOT 4 — GitHub Repository**
- **When:** Open browser, go to your GitHub repo
- **What to show:** Full repo page showing files + commit count + branches
- **Why:** Proves code was pushed to GitHub (worth 2 marks)
- **Save as:** `part-a-github-repo.png`

---

📸 **SCREENSHOT 5 — .gitignore**
- **When:** After running `cat ~/assignment3/.gitignore`
- **What to show:** File content showing `__pycache__/`, `.env`, `.vscode/`, `.DS_Store`
- **Why:** Proves proper .gitignore (worth 2 marks)
- **Save as:** `part-a-gitignore.png`

---

### Part A Mini Checklist
- [ ] `git config` shows name + email
- [ ] `git branch -a` shows 3+ branches
- [ ] `git log --oneline` shows 10+ commits
- [ ] GitHub repo is public and accessible
- [ ] `.gitignore` has all required exclusions
- [ ] All 5 screenshots collected

---

---

## PART B GUIDE — Containerization with Docker (20 marks)

> ✅ You said Part B is already done. Skip to **Recovery Screenshot Steps** below.  
> If anything is not running, use the fresh setup commands in each section.

---

### B — Recovery Screenshot Steps

**Where to run:** Ubuntu VM terminal

```bash
# Navigate to app directory
cd ~/assignment3/app

# Make sure containers are running
docker compose up -d

# Wait ~30 seconds for MySQL to initialize, then:

# 1. List running containers
docker ps

# 2. Show Docker networks
docker network ls

# 3. Inspect the custom app network
docker network inspect app-network

# 4. Show volumes
docker volume ls

# 5. Test health endpoint
curl http://localhost/health

# 6. Create a test item
curl -X POST http://localhost/api/items \
  -H "Content-Type: application/json" \
  -d '{"name": "Test Item", "description": "Docker test"}'

# 7. List items (proves API + DB are connected)
curl http://localhost/api/items

# 8. Test persistence: bring down without deleting volumes, then back up
docker compose down
docker compose up -d
# Wait ~30 seconds
curl http://localhost/api/items
# Data should still be there (proves volume persistence)
```

---

📸 **SCREENSHOT 6 — Docker Containers Running**
- **When:** After `docker ps` with all 3 containers up
- **What to show:** nginx, flask-api, and mysql containers all with STATUS "Up"
- **Why:** Proves Docker Compose orchestration (6 marks)
- **Save as:** `part-b-docker-ps.png`

---

📸 **SCREENSHOT 7 — Docker Networks**
- **When:** After `docker network ls`
- **What to show:** `app-network` (or `assignment3_app-network`) in the list
- **Why:** Proves custom bridge network created (4 marks)
- **Save as:** `part-b-docker-networks.png`

---

📸 **SCREENSHOT 8 — Network Inspection**
- **When:** After `docker network inspect app-network`
- **What to show:** JSON output showing all 3 containers listed under "Containers"
- **Why:** Proves inter-container communication on custom bridge network
- **Save as:** `part-b-network-inspect.png`

---

📸 **SCREENSHOT 9 — Docker Volumes**
- **When:** After `docker volume ls`
- **What to show:** `mysql-data` (or `assignment3_mysql-data`) volume listed
- **Why:** Proves named volume created (4 marks)
- **Save as:** `part-b-docker-volumes.png`

---

📸 **SCREENSHOT 10 — Health Endpoint**
- **When:** After `curl http://localhost/health`
- **What to show:** `{"service":"flask-api","status":"healthy"}`
- **Why:** Proves full stack is working (Nginx → Flask)
- **Save as:** `part-b-health-check.png`

---

📸 **SCREENSHOT 11 — Create Item**
- **When:** After the POST curl command
- **What to show:** `{"id":1,"name":"Test Item","description":"Docker test"}`
- **Why:** Proves Flask API + MySQL are connected
- **Save as:** `part-b-create-item.png`

---

📸 **SCREENSHOT 12 — Volume Persistence**
- **When:** After `docker compose down` + `docker compose up -d` + `curl /api/items`
- **What to show:** The item you created earlier still appears in the list
- **Why:** Proves data persistence across container restarts (4 marks)
- **Save as:** `part-b-volume-persistence.png`

---

### Part B — File Verification

Make sure these files exist:

```bash
ls ~/assignment3/app/nginx/Dockerfile
ls ~/assignment3/app/flask-api/Dockerfile
ls ~/assignment3/app/docker-compose.yml
cat ~/assignment3/app/nginx/Dockerfile
cat ~/assignment3/app/flask-api/Dockerfile
```

📸 **SCREENSHOT 13 — Dockerfiles**
- **When:** After `cat` of both Dockerfiles
- **What to show:** Both Dockerfile contents visible
- **Why:** Proves correct Dockerfile setup (6 marks)
- **Save as:** `part-b-dockerfiles.png`

---

### Part B Mini Checklist
- [ ] All 3 containers running (`docker ps`)
- [ ] Custom bridge network exists and all containers on it
- [ ] Named volume `mysql-data` exists
- [ ] `curl /health` returns healthy
- [ ] POST `/api/items` works
- [ ] Data survives `docker compose down` + `up`
- [ ] Both Dockerfiles correct
- [ ] All 8 screenshots collected

---

---

## PART C GUIDE — CI/CD with GitHub Actions (15 marks)

> ⚠️ You need to complete this if not done yet.

---

### C1 — Setup DockerHub

**Where:** Browser

1. Go to [hub.docker.com](https://hub.docker.com) and create a free account if you don't have one.
2. Go to: **Account Settings → Security → New Access Token**
3. Name it: `github-actions`
4. Copy the token immediately (you won't see it again).

---

### C2 — Add GitHub Secrets

**Where:** Browser → Your GitHub repo

1. Go to your repo → **Settings → Secrets and variables → Actions**
2. Click **New repository secret**
3. Add:
   - Name: `DOCKERHUB_USERNAME` → Value: your DockerHub username
   - Name: `DOCKERHUB_TOKEN` → Value: the token you copied

📸 **SCREENSHOT 14 — GitHub Secrets**
- **When:** After adding both secrets
- **What to show:** Both secrets listed (values are hidden, that's fine)
- **Why:** Proves no hardcoded credentials (2 marks)
- **Save as:** `part-c-github-secrets.png`

---

### C3 — Create CI/CD Workflow File

**Where:** Ubuntu VM terminal

```bash
mkdir -p ~/assignment3/.github/workflows
nano ~/assignment3/.github/workflows/ci-cd.yml
```

Paste this exactly (replace nothing — secrets handle the username):

```yaml
name: CI/CD Pipeline

on:
  push:
    branches: [main]
  pull_request:
    branches: [main]

jobs:
  build-and-push:
    runs-on: ubuntu-latest

    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Login to DockerHub
        uses: docker/login-action@v3
        with:
          username: ${{ secrets.DOCKERHUB_USERNAME }}
          password: ${{ secrets.DOCKERHUB_TOKEN }}

      - name: Build and push Flask API image
        uses: docker/build-push-action@v5
        with:
          context: ./app/flask-api
          push: true
          tags: ${{ secrets.DOCKERHUB_USERNAME }}/flask-api:latest

      - name: Build and push Nginx image
        uses: docker/build-push-action@v5
        with:
          context: ./app/nginx
          push: true
          tags: ${{ secrets.DOCKERHUB_USERNAME }}/nginx-proxy:latest
```

Save: `Ctrl+O` → Enter → `Ctrl+X`

---

### C4 — Commit and Push to Trigger Pipeline

```bash
cd ~/assignment3

# Make sure you're on main branch
git checkout main

git add .github/workflows/ci-cd.yml
git commit -m "feat: add GitHub Actions CI/CD pipeline"
git push origin main
```

What this does: pushing to `main` triggers the GitHub Actions workflow automatically.

---

### C5 — Verify Pipeline Ran

**Where:** Browser → Your GitHub repo → **Actions** tab

Wait 2–3 minutes. You should see a green checkmark.

📸 **SCREENSHOT 15 — GitHub Actions Workflow Success**
- **When:** After the workflow finishes (green checkmark)
- **What to show:** Workflow run page showing all steps green ✅
- **Why:** Proves CI/CD pipeline works (main proof for 15 marks)
- **Save as:** `part-c-github-actions-success.png`

---

📸 **SCREENSHOT 16 — DockerHub Images**
- **When:** After workflow finishes, go to hub.docker.com
- **What to show:** Both `flask-api` and `nginx-proxy` repos visible with "last pushed" timestamp
- **Why:** Proves images were built and pushed (8 marks)
- **Save as:** `part-c-dockerhub-images.png`

---

### Part C Mini Checklist
- [ ] DockerHub account created
- [ ] Access token created
- [ ] Both GitHub secrets added
- [ ] `ci-cd.yml` file created in correct path
- [ ] Pushed to `main` branch
- [ ] GitHub Actions shows green checkmark
- [ ] Both images visible on DockerHub
- [ ] 3 screenshots collected

---

---

## PART D-1 GUIDE — Namespace & Deployments (10 marks)

### D1.1 — Start Minikube

**Where:** Ubuntu VM terminal

```bash
# Start Minikube (uses Docker as driver)
minikube start --driver=docker --memory=2048 --cpus=2

# Verify it's running
minikube status
kubectl get nodes
```

Expected output: `minikube   Ready   control-plane`

📸 **SCREENSHOT 17 — Minikube Running**
- **When:** After `minikube status` and `kubectl get nodes`
- **What to show:** Both commands showing Running/Ready status
- **Why:** Proves Minikube is up
- **Save as:** `part-d1-minikube-status.png`

---

### D1.2 — Create Directory Structure

```bash
mkdir -p ~/assignment3/k8s
cd ~/assignment3
```

---

### D1.3 — Create Namespace

```bash
cat > ~/assignment3/k8s/namespace.yml << 'EOF'
apiVersion: v1
kind: Namespace
metadata:
  name: assignment3
EOF

kubectl apply -f ~/assignment3/k8s/namespace.yml
kubectl get namespaces
```

---

### D1.4 — Create MySQL Deployment

> ⚠️ Do D4 (Secrets + ConfigMaps) BEFORE applying deployments. They are shown here together for file creation — apply in the correct order in D4.

```bash
cat > ~/assignment3/k8s/mysql-deployment.yml << 'EOF'
apiVersion: apps/v1
kind: Deployment
metadata:
  name: mysql
  namespace: assignment3
  labels:
    app: mysql
spec:
  replicas: 1
  selector:
    matchLabels:
      app: mysql
  template:
    metadata:
      labels:
        app: mysql
    spec:
      containers:
        - name: mysql
          image: mysql:8.0
          ports:
            - containerPort: 3306
          env:
            - name: MYSQL_ROOT_PASSWORD
              valueFrom:
                secretKeyRef:
                  name: mysql-secret
                  key: mysql_root_password
            - name: MYSQL_DATABASE
              valueFrom:
                secretKeyRef:
                  name: mysql-secret
                  key: mysql_database
            - name: MYSQL_USER
              valueFrom:
                secretKeyRef:
                  name: mysql-secret
                  key: mysql_user
            - name: MYSQL_PASSWORD
              valueFrom:
                secretKeyRef:
                  name: mysql-secret
                  key: mysql_password
          volumeMounts:
            - name: mysql-storage
              mountPath: /var/lib/mysql
          resources:
            requests:
              memory: "256Mi"
              cpu: "250m"
            limits:
              memory: "512Mi"
              cpu: "500m"
      volumes:
        - name: mysql-storage
          persistentVolumeClaim:
            claimName: mysql-pvc
EOF
```

---

### D1.5 — Create Flask API Deployment

> Replace `YOUR_DOCKERHUB_USERNAME` with your actual DockerHub username.

```bash
DHUSER="YOUR_DOCKERHUB_USERNAME"

cat > ~/assignment3/k8s/flask-deployment.yml << EOF
apiVersion: apps/v1
kind: Deployment
metadata:
  name: flask-api
  namespace: assignment3
  labels:
    app: flask-api
spec:
  replicas: 1
  selector:
    matchLabels:
      app: flask-api
  template:
    metadata:
      labels:
        app: flask-api
    spec:
      containers:
        - name: flask-api
          image: ${DHUSER}/flask-api:latest
          ports:
            - containerPort: 5000
          env:
            - name: DB_HOST
              valueFrom:
                configMapKeyRef:
                  name: flask-config
                  key: db_host
            - name: DB_USER
              valueFrom:
                secretKeyRef:
                  name: mysql-secret
                  key: mysql_user
            - name: DB_PASSWORD
              valueFrom:
                secretKeyRef:
                  name: mysql-secret
                  key: mysql_password
            - name: DB_NAME
              valueFrom:
                configMapKeyRef:
                  name: flask-config
                  key: db_name
          readinessProbe:
            httpGet:
              path: /health
              port: 5000
            initialDelaySeconds: 10
            periodSeconds: 5
          livenessProbe:
            httpGet:
              path: /health
              port: 5000
            initialDelaySeconds: 30
            periodSeconds: 10
          resources:
            requests:
              memory: "128Mi"
              cpu: "100m"
            limits:
              memory: "256Mi"
              cpu: "250m"
EOF
```

---

### D1.6 — Create Nginx Deployment

```bash
cat > ~/assignment3/k8s/nginx-deployment.yml << EOF
apiVersion: apps/v1
kind: Deployment
metadata:
  name: nginx
  namespace: assignment3
  labels:
    app: nginx
spec:
  replicas: 1
  selector:
    matchLabels:
      app: nginx
  template:
    metadata:
      labels:
        app: nginx
    spec:
      containers:
        - name: nginx
          image: ${DHUSER}/nginx-proxy:latest
          ports:
            - containerPort: 80
          volumeMounts:
            - name: nginx-config
              mountPath: /etc/nginx/conf.d
          resources:
            requests:
              memory: "64Mi"
              cpu: "50m"
            limits:
              memory: "128Mi"
              cpu: "100m"
      volumes:
        - name: nginx-config
          configMap:
            name: nginx-config
EOF
```

---

> ⚠️ **DO NOT APPLY DEPLOYMENTS YET.** First complete D3 (PV/PVC) and D4 (Secrets/ConfigMaps), then apply everything in D4's apply order.

---

### Part D-1 Mini Checklist
- [ ] Minikube running
- [ ] `k8s/namespace.yml` created
- [ ] `k8s/mysql-deployment.yml` created
- [ ] `k8s/flask-deployment.yml` created (with your DockerHub username)
- [ ] `k8s/nginx-deployment.yml` created (with your DockerHub username)

---

---

## PART D-2 GUIDE — Services & Networking (10 marks)

### D2.1 — Create All Service Files

```bash
# MySQL Service (ClusterIP - internal only)
cat > ~/assignment3/k8s/mysql-service.yml << 'EOF'
apiVersion: v1
kind: Service
metadata:
  name: mysql
  namespace: assignment3
spec:
  type: ClusterIP
  selector:
    app: mysql
  ports:
    - port: 3306
      targetPort: 3306
EOF

# Flask API Service (ClusterIP - internal only)
cat > ~/assignment3/k8s/flask-service.yml << 'EOF'
apiVersion: v1
kind: Service
metadata:
  name: flask-api
  namespace: assignment3
spec:
  type: ClusterIP
  selector:
    app: flask-api
  ports:
    - port: 5000
      targetPort: 5000
EOF

# Nginx Service (NodePort - external access on port 30080)
cat > ~/assignment3/k8s/nginx-service.yml << 'EOF'
apiVersion: v1
kind: Service
metadata:
  name: nginx
  namespace: assignment3
spec:
  type: NodePort
  selector:
    app: nginx
  ports:
    - port: 80
      targetPort: 80
      nodePort: 30080
EOF
```

> ⚠️ **Do NOT apply yet.** Apply everything together in D4's apply sequence.

---

### Part D-2 Mini Checklist
- [ ] `k8s/mysql-service.yml` created (ClusterIP)
- [ ] `k8s/flask-service.yml` created (ClusterIP)
- [ ] `k8s/nginx-service.yml` created (NodePort 30080)

---

---

## PART D-3 GUIDE — Persistent Storage (10 marks)

### D3.1 — Create PersistentVolume and PVC

```bash
# PersistentVolume (cluster-level, no namespace)
cat > ~/assignment3/k8s/mysql-pv.yml << 'EOF'
apiVersion: v1
kind: PersistentVolume
metadata:
  name: mysql-pv
spec:
  storageClassName: manual
  capacity:
    storage: 1Gi
  accessModes:
    - ReadWriteOnce
  persistentVolumeReclaimPolicy: Retain
  hostPath:
    path: /data/mysql
EOF

# PersistentVolumeClaim (inside namespace)
cat > ~/assignment3/k8s/mysql-pvc.yml << 'EOF'
apiVersion: v1
kind: PersistentVolumeClaim
metadata:
  name: mysql-pvc
  namespace: assignment3
spec:
  storageClassName: manual
  accessModes:
    - ReadWriteOnce
  resources:
    requests:
      storage: 1Gi
EOF
```

> ⚠️ **Do NOT apply yet.** Apply in D4's sequence.

---

### Part D-3 Mini Checklist
- [ ] `k8s/mysql-pv.yml` created
- [ ] `k8s/mysql-pvc.yml` created

---

---

## PART D-4 GUIDE — ConfigMaps & Secrets + Apply Everything (10 marks)

### D4.1 — Create Secret File

```bash
cat > ~/assignment3/k8s/mysql-secret.yml << 'EOF'
apiVersion: v1
kind: Secret
metadata:
  name: mysql-secret
  namespace: assignment3
type: Opaque
data:
  mysql_root_password: cm9vdHBhc3M=
  mysql_user: Zmxhc2t1c2Vy
  mysql_password: Zmxhc2twYXNz
  mysql_database: Zmxhc2tkYg==
EOF
```

These are base64 encoded. Plain values: rootpass / flaskuser / flaskpass / flaskdb

---

### D4.2 — Create Flask ConfigMap

```bash
cat > ~/assignment3/k8s/flask-configmap.yml << 'EOF'
apiVersion: v1
kind: ConfigMap
metadata:
  name: flask-config
  namespace: assignment3
data:
  db_host: "mysql"
  db_name: "flaskdb"
  app_env: "production"
EOF
```

---

### D4.3 — Create Nginx ConfigMap

```bash
cat > ~/assignment3/k8s/nginx-configmap.yml << 'EOF'
apiVersion: v1
kind: ConfigMap
metadata:
  name: nginx-config
  namespace: assignment3
data:
  default.conf: |
    upstream flask_api {
        server flask-api:5000;
    }
    server {
        listen 80;
        server_name localhost;
        location / {
            proxy_pass http://flask_api;
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
        }
    }
EOF
```

---

### D4.4 — Apply Everything in Correct Order

```bash
cd ~/assignment3

kubectl apply -f k8s/namespace.yml
sleep 2

kubectl apply -f k8s/mysql-secret.yml
kubectl apply -f k8s/flask-configmap.yml
kubectl apply -f k8s/nginx-configmap.yml

kubectl apply -f k8s/mysql-pv.yml
kubectl apply -f k8s/mysql-pvc.yml

kubectl apply -f k8s/mysql-deployment.yml
kubectl apply -f k8s/mysql-service.yml

echo "Waiting for MySQL to be ready..."
kubectl wait --for=condition=Ready pod -l app=mysql -n assignment3 --timeout=120s

kubectl apply -f k8s/flask-deployment.yml
kubectl apply -f k8s/flask-service.yml

kubectl apply -f k8s/nginx-configmap.yml
kubectl apply -f k8s/nginx-deployment.yml
kubectl apply -f k8s/nginx-service.yml

echo "Waiting for all pods..."
kubectl wait --for=condition=Ready pod --all -n assignment3 --timeout=180s

kubectl get all -n assignment3
```

Expected: all deployments show READY, all pods Running.

---

### D4.5 — Verify ConfigMaps and Secrets

```bash
kubectl get secrets -n assignment3
kubectl get configmaps -n assignment3
kubectl describe secret mysql-secret -n assignment3
kubectl describe configmap flask-config -n assignment3
```

---

📸 **SCREENSHOT 18 — All Resources Running**
- **When:** After `kubectl get all -n assignment3`
- **What to show:** All deployments READY, all pods Running, all services listed
- **Why:** Core proof for D1+D2 (20 marks combined)
- **Save as:** `part-d1-kubectl-get-all.png`

---

📸 **SCREENSHOT 19 — PV and PVC Bound**
- **When:** After running:
  ```bash
  kubectl get pv
  kubectl get pvc -n assignment3
  ```
- **What to show:** `mysql-pv` STATUS = **Bound**, `mysql-pvc` STATUS = **Bound**
- **Why:** Proves persistent storage setup (D3, 10 marks)
- **Save as:** `part-d3-pv-pvc-bound.png`

---

📸 **SCREENSHOT 20 — Secrets and ConfigMaps**
- **When:** After `kubectl get secrets` and `kubectl get configmaps`
- **What to show:** `mysql-secret`, `flask-config`, `nginx-config` all listed
- **Why:** Proves D4 (10 marks)
- **Save as:** `part-d4-secrets-configmaps.png`

---

### Part D-4 Mini Checklist
- [ ] `k8s/mysql-secret.yml` created
- [ ] `k8s/flask-configmap.yml` created
- [ ] `k8s/nginx-configmap.yml` created
- [ ] All manifests applied in correct order
- [ ] All pods Running
- [ ] PV + PVC both show Bound
- [ ] Secrets + ConfigMaps verified
- [ ] 3 screenshots collected

---

---

## PART D-5 GUIDE — Scaling & Updates (10 marks)

### D5.1 — Scale Flask to 3 Replicas

```bash
kubectl scale deployment flask-api --replicas=3 -n assignment3

# Verify (run this immediately after)
kubectl get pods -n assignment3 -l app=flask-api
```

Expected: 3 pods all showing Running.

📸 **SCREENSHOT 21 — 3 Flask Pods Running**
- **When:** After scaling and verifying with `kubectl get pods -l app=flask-api`
- **What to show:** 3 flask-api pods, all STATUS = Running
- **Why:** Proves scaling (3 marks)
- **Save as:** `part-d5-scaling-3-pods.png`

---

### D5.2 — Rolling Update

First, build and push a v2 image:

```bash
# Make a small change to app.py for v2
cd ~/assignment3/app/flask-api

# Add version field to health response
sed -i "s/return jsonify({'status': 'healthy', 'service': 'flask-api'})/return jsonify({'status': 'healthy', 'service': 'flask-api', 'version': 'v2'})/" app.py

# Build and push v2
DHUSER="YOUR_DOCKERHUB_USERNAME"
docker build -t ${DHUSER}/flask-api:v2 .
docker push ${DHUSER}/flask-api:v2
```

Now trigger the rolling update:

```bash
kubectl set image deployment/flask-api flask-api=${DHUSER}/flask-api:v2 -n assignment3

# Watch the update happen in real time
kubectl rollout status deployment/flask-api -n assignment3
```

📸 **SCREENSHOT 22 — Rolling Update**
- **When:** While/after `kubectl rollout status` completes
- **What to show:** "successfully rolled out" message
- **Why:** Proves rolling update (3 marks)
- **Save as:** `part-d5-rolling-update.png`

---

### D5.3 — Rollback

```bash
# Check rollout history
kubectl rollout history deployment/flask-api -n assignment3

# Rollback
kubectl rollout undo deployment/flask-api -n assignment3

# Confirm rollback
kubectl rollout status deployment/flask-api -n assignment3
kubectl describe deployment flask-api -n assignment3 | grep Image
```

📸 **SCREENSHOT 23 — Rollback Success**
- **When:** After `kubectl rollout undo` and `kubectl describe | grep Image`
- **What to show:** Rollback confirmation message + image reverting to `:latest`
- **Why:** Proves rollback capability (3 marks)
- **Save as:** `part-d5-rollback.png`

---

### Part D-5 Mini Checklist
- [ ] Flask scaled to 3 replicas
- [ ] v2 image built and pushed to DockerHub
- [ ] Rolling update performed
- [ ] Rollback performed
- [ ] 3 screenshots collected

---

---

## PART D-6 GUIDE — End-to-End Verification (5 marks)

### D6.1 — Get Minikube IP and Access App

```bash
# Get the URL
minikube service nginx -n assignment3 --url

# Or use NodePort directly
MINK_IP=$(minikube ip)
echo "App URL: http://${MINK_IP}:30080"

# Test health
curl http://${MINK_IP}:30080/health
```

Expected: `{"service":"flask-api","status":"healthy"}`

---

### D6.2 — Test Full CRUD

```bash
MINK_IP=$(minikube ip)

# Create an item
curl -X POST http://${MINK_IP}:30080/api/items \
  -H "Content-Type: application/json" \
  -d '{"name": "Kubernetes Item", "description": "Created on K8s"}'

# List all items
curl http://${MINK_IP}:30080/api/items
```

📸 **SCREENSHOT 24 — End-to-End Curl Output**
- **When:** After running all curl commands
- **What to show:** Health check response + POST response + GET response with item
- **Why:** Proves application accessible via NodePort (2 marks)
- **Save as:** `part-d6-e2e-curl.png`

---

### D6.3 — Self-Healing Demonstration

```bash
MINK_IP=$(minikube ip)

# Get current flask pod name
kubectl get pods -n assignment3 -l app=flask-api

# Delete one pod (Kubernetes will recreate it automatically)
FLASK_POD=$(kubectl get pod -l app=flask-api -n assignment3 -o jsonpath='{.items[0].metadata.name}')
kubectl delete pod ${FLASK_POD} -n assignment3

# Watch Kubernetes recreate it (press Ctrl+C after new pod is Running)
kubectl get pods -n assignment3 -l app=flask-api -w
```

📸 **SCREENSHOT 25 — Self-Healing**
- **When:** While watching pods with `-w` — capture the moment old pod terminates and new one starts
- **What to show:** Old pod Terminating + new pod appearing (ContainerCreating → Running)
- **Why:** Proves self-healing (1.5 marks)
- **Save as:** `part-d6-self-healing.png`

---

### D6.4 — Data Persistence After MySQL Pod Deletion

```bash
MINK_IP=$(minikube ip)

# First make sure there's data
curl http://${MINK_IP}:30080/api/items

# Delete MySQL pod
MYSQL_POD=$(kubectl get pod -l app=mysql -n assignment3 -o jsonpath='{.items[0].metadata.name}')
kubectl delete pod ${MYSQL_POD} -n assignment3

# Watch MySQL pod recreate
kubectl get pods -n assignment3 -l app=mysql -w

# Wait for it to be Running, then verify data still exists
curl http://${MINK_IP}:30080/api/items
```

📸 **SCREENSHOT 26 — Persistence After MySQL Pod Deletion**
- **When:** After MySQL pod recreates and `curl /api/items` returns your data
- **What to show:** Terminal showing old pod deleted + new pod running + curl returning items
- **Why:** Proves data persistence via PVC (1.5 marks)
- **Save as:** `part-d6-persistence-proof.png`

---

### Part D-6 Mini Checklist
- [ ] App accessible via `minikube ip`:30080
- [ ] Health endpoint returns healthy
- [ ] POST and GET items working
- [ ] Flask pod deleted and recreated automatically
- [ ] MySQL pod deleted + data still there after recreation
- [ ] 3 screenshots collected

---

---

## STARTUP SCRIPT

Create the required `start.sh` that your instructor will run:

```bash
cat > ~/assignment3/start.sh << 'EOF'
#!/bin/bash

cd ~/assignment3

echo "Starting Minikube..."
minikube start --driver=docker --memory=2048 --cpus=2

echo "Waiting for Minikube to be ready..."
kubectl wait --for=condition=Ready node/minikube --timeout=120s

echo "Applying Kubernetes manifests..."
kubectl apply -f k8s/namespace.yml
sleep 2
kubectl apply -f k8s/mysql-secret.yml
kubectl apply -f k8s/flask-configmap.yml
kubectl apply -f k8s/mysql-pv.yml
kubectl apply -f k8s/mysql-pvc.yml
kubectl apply -f k8s/mysql-deployment.yml
kubectl apply -f k8s/mysql-service.yml

echo "Waiting for MySQL to be ready..."
kubectl wait --for=condition=Ready pod -l app=mysql -n assignment3 --timeout=120s

kubectl apply -f k8s/flask-deployment.yml
kubectl apply -f k8s/flask-service.yml
kubectl apply -f k8s/nginx-configmap.yml
kubectl apply -f k8s/nginx-deployment.yml
kubectl apply -f k8s/nginx-service.yml

echo "Waiting for all pods to be ready..."
kubectl wait --for=condition=Ready pod --all -n assignment3 --timeout=180s

echo ""
echo "=== Deployment Status ==="
kubectl get all -n assignment3

echo ""
echo "=== Access URL ==="
minikube service nginx -n assignment3 --url
EOF

chmod +x ~/assignment3/start.sh
```

---

---

## FINAL SUBMISSION CHECKLIST

### Git & Code
- [ ] All code committed to GitHub
- [ ] 10+ meaningful commits
- [ ] 3+ branches used (main, develop, feature/...)
- [ ] `.gitignore` present with correct exclusions
- [ ] GitHub repo is public

### Docker
- [ ] Nginx Dockerfile exists at `app/nginx/Dockerfile`
- [ ] Flask Dockerfile exists at `app/flask-api/Dockerfile`
- [ ] `docker-compose.yml` orchestrates all 3 services
- [ ] Custom bridge network + named MySQL volume
- [ ] `curl http://localhost/health` returns healthy

### CI/CD
- [ ] `.github/workflows/ci-cd.yml` exists
- [ ] GitHub Actions shows green checkmark on main
- [ ] `flask-api:latest` visible on DockerHub
- [ ] `nginx-proxy:latest` visible on DockerHub
- [ ] No hardcoded credentials (secrets used)

### Kubernetes Files (all in `k8s/`)
- [ ] `namespace.yml`
- [ ] `mysql-secret.yml`
- [ ] `flask-configmap.yml`
- [ ] `nginx-configmap.yml`
- [ ] `mysql-pv.yml`
- [ ] `mysql-pvc.yml`
- [ ] `mysql-deployment.yml`
- [ ] `mysql-service.yml`
- [ ] `flask-deployment.yml`
- [ ] `flask-service.yml`
- [ ] `nginx-deployment.yml`
- [ ] `nginx-service.yml`

### Kubernetes Verification
- [ ] `kubectl get namespaces` shows `assignment3`
- [ ] `kubectl get all -n assignment3` shows all pods Running
- [ ] `kubectl get pv` shows mysql-pv STATUS = Bound
- [ ] `kubectl get pvc -n assignment3` shows mysql-pvc STATUS = Bound
- [ ] `kubectl get secrets -n assignment3` shows mysql-secret
- [ ] `kubectl get configmaps -n assignment3` shows flask-config + nginx-config
- [ ] Flask scaled to 3 replicas
- [ ] Rolling update performed
- [ ] Rollback performed
- [ ] App accessible at `$(minikube ip):30080`
- [ ] Self-healing demonstrated
- [ ] Data persists after MySQL pod deletion

### Startup Script
- [ ] `start.sh` exists at `~/assignment3/start.sh`
- [ ] `start.sh` is executable (`chmod +x`)
- [ ] `start.sh` tested and works

### Screenshots Collected (26 total)
- [ ] part-a-git-config.png
- [ ] part-a-git-branches.png
- [ ] part-a-git-log.png
- [ ] part-a-github-repo.png
- [ ] part-a-gitignore.png
- [ ] part-b-docker-ps.png
- [ ] part-b-docker-networks.png
- [ ] part-b-network-inspect.png
- [ ] part-b-docker-volumes.png
- [ ] part-b-health-check.png
- [ ] part-b-create-item.png
- [ ] part-b-volume-persistence.png
- [ ] part-b-dockerfiles.png
- [ ] part-c-github-secrets.png
- [ ] part-c-github-actions-success.png
- [ ] part-c-dockerhub-images.png
- [ ] part-d1-minikube-status.png
- [ ] part-d1-kubectl-get-all.png
- [ ] part-d3-pv-pvc-bound.png
- [ ] part-d4-secrets-configmaps.png
- [ ] part-d5-scaling-3-pods.png
- [ ] part-d5-rolling-update.png
- [ ] part-d5-rollback.png
- [ ] part-d6-e2e-curl.png
- [ ] part-d6-self-healing.png
- [ ] part-d6-persistence-proof.png

### Final Submission
- [ ] Stop Minikube: `minikube stop`
- [ ] Export VM: VirtualBox → File → Export Appliance → `.ova`
- [ ] File name: `RollNumber_Assignment3.ova`
- [ ] Upload `.ova` to Google Drive
- [ ] Set Google Drive sharing: "Anyone with the link can **edit**"
- [ ] Build PDF report with all screenshots + YAML explanations + architecture diagram
- [ ] File name: `RollNumber_Assignment3_Report.pdf`
- [ ] Submit Drive link + PDF on Google Classroom before **Jun 3, 11:59 PM**

---

## PDF Report Sections Checklist

Your report must include:

1. **Architecture Diagram** — draw the 3-tier system (Nginx → Flask → MySQL) with K8s concepts labeled
2. **Part A section** — screenshots 1–5
3. **Part B section** — screenshots 6–13
4. **Part C section** — screenshots 14–16
5. **Part D section** — screenshots 17–26
6. **YAML Explanations** — one paragraph per manifest explaining what it does and why
7. **Service Types Explanation** — why ClusterIP for MySQL/Flask, NodePort for Nginx

---

*Good luck. Start early. Test each part before moving to the next.*
