const express = require("express");

const app = express();
const PORT = process.env.PORT || 3000;

// GET /api/version
// Retorna informações básicas sobre a aplicação (nome e versão).
app.get("/api/version", (req, res) => {
  res.json({
    appName: "Gerenciador de Tarefas Multi_usuario",
    version: "1.0.0",
  });
});

app.listen(PORT, () => {
  console.log(`Servidor rodando em http://localhost:${PORT}`);
  console.log(`Endpoint disponível em http://localhost:${PORT}/api/version`);
});