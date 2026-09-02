FROM debian:bookworm-slim
RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        binutils ca-certificates cmake gcc-multilib make python3 \
    && rm -rf /var/lib/apt/lists/*
WORKDIR /workspace
CMD ["python3", "-B", "tools/run_linux_i386_build.py"]
