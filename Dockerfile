# Use an image with CUDA and Ubuntu (for GPU support, modify accordingly)
FROM nvidia/cuda:12.6.2-cudnn-runtime-ubuntu24.04

# Install basic utilities
RUN apt-get update && apt-get install -y wget git vim make gcc libglib2.0-0 libgl1

# Set working directory
WORKDIR /workspace

# Copy any necessary files for initial setup
COPY . /workspace

# Start the system dashboard script
CMD ["/workspace/system_dashboard.sh"]

# When ready to set up, from '~/dev/system_dashboard', run:
# `docker build -t mchieberly/system_dashboard:latest .`
# `docker push mchieberly/system_dashboard:latest`

# To run the docker container locally, run:
# `docker run --name system_dashboard mchieberly/system_dashboard:latest`
