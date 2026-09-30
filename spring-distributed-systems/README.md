# 🐇 Spring: Sistemas Distribuídos e Mensageria

> Sistema de pedidos com Spring Boot, REST e RabbitMQ, com processamento assíncrono orientado a eventos. Desenvolvido na disciplina de Sistemas Distribuídos da graduação de ADS.

<div align="center">

![Java](https://img.shields.io/badge/Java-17+-ED8B00?style=for-the-badge&logo=openjdk&logoColor=white)
![Spring Boot](https://img.shields.io/badge/Spring_Boot-3.5-6DB33F?style=for-the-badge&logo=springboot&logoColor=white)
![RabbitMQ](https://img.shields.io/badge/RabbitMQ-4-FF6600?style=for-the-badge&logo=rabbitmq&logoColor=white)
![Docker](https://img.shields.io/badge/Docker-2496ED?style=for-the-badge&logo=docker&logoColor=white)

</div>

---

## 📖 Sobre o projeto

Em uma API tradicional, o cliente espera até que **todo** o processamento termine: gravar o pedido, atualizar o estoque, registrar o pagamento, enviar a notificação... Com mensageria, a API só **publica um evento** e responde na hora (`202 Accepted`). Os demais serviços processam a mensagem de forma assíncrona e independente.

A API não chama estoque, pagamento nem notificação diretamente. Ela conhece apenas a **exchange**. Por isso os serviços ficam com **baixo acoplamento**.

---

## 🚀 Tecnologias e Ferramentas

| Tecnologia | Utilização |
|---|---|
| ☕ **Java 17** | Linguagem de programação |
| 🍃 **Spring Boot 3.5** (`web`, `amqp`, `validation`) | API REST, integração com RabbitMQ e validação |
| 🐇 **RabbitMQ 4** | Broker de mensagens (protocolo AMQP) |
| 🐳 **Docker / Docker Compose** | Ambiente padronizado do broker |
| 🧪 **JUnit 5 + REST Client** | Testes unitários e testes dos endpoints |

## 📘 Conceitos Praticados

- **Produtor, broker e consumidor**: `RabbitTemplate` para publicar e `@RabbitListener` para consumir.
- **Default exchange**: envio direto pelo nome da fila (Etapas 1 e 2).
- **Exchange TOPIC e routing keys**: eventos `pedido.criado`, `pedido.pago` e `pedido.cancelado`, com bindings exatos e curinga (`pedido.*`).
- **Serialização JSON**: objetos Java publicados e consumidos como JSON (`Jackson2JsonMessageConverter`).
- **Tratamento de mensagens inválidas**: validação no consumidor, rejeição sem requeue e **Dead Letter Queue**.
- **Retry seletivo**: falhas transitórias são reprocessadas até 3 vezes. Mensagens inválidas vão direto para a DLQ.
- **REST x Mensageria**: a API síncrona convive com o processamento assíncrono.

---

## 🏗️ Arquitetura

```
Cliente
   |
   | POST /pedidos  (202 Accepted)
   v
+---------------+
|  Pedido API   |  PedidoController → PedidoService → PedidoProducer
+-------+-------+
        |
        v
+---------------------------+
| pedidos.exchange (TOPIC)  |
+-------------+-------------+
              |
   +----------+-----------------+--------------------------+
   | pedido.criado              | pedido.pago              | pedido.*
   | pedido.cancelado           | pedido.cancelado         |
   v                            v                          v
estoque.queue            financeiro.queue          notificacao.queue
   |                            |                          |
EstoqueConsumer          PagamentoConsumer         NotificacaoConsumer
   \                            |                          /
    +------ mensagens rejeitadas (dead letter) -----------+
                                |
                                v
                  pedidos.dlx (DIRECT) → pedidos.dlq → DeadLetterConsumer
```

### Quem recebe cada evento

| Evento (routing key) | estoque.queue | financeiro.queue | notificacao.queue |
|---|:---:|:---:|:---:|
| `pedido.criado` | ✅ reserva estoque | — | ✅ "recebemos seu pedido" |
| `pedido.pago` | — | ✅ registra pagamento | ✅ "pagamento confirmado" |
| `pedido.cancelado` | ✅ devolve estoque | ✅ cancela cobrança | ✅ "pedido cancelado" |

---

## ▶️ Como executar

**Pré-requisitos:** Docker, Java 17+ e Maven.

```bash
# 1. Subir o RabbitMQ
docker compose up -d

# 2. Rodar a aplicação (porta 8080)
mvn spring-boot:run

# 3. Rodar os testes
mvn test
```

Management UI: **http://localhost:15672** (usuário `guest`, senha `guest`).
Em **Exchanges** e **Queues and Streams** dá para ver a topologia criada automaticamente, os bindings, as taxas de publish/deliver e o tamanho de cada fila.

| Porta | Uso |
|---|---|
| `5672` | Comunicação AMQP (aplicação ↔ broker) |
| `15672` | Interface de gerenciamento HTTP |
| `8080` | API REST |

---

## 🌐 Endpoints

Todos os exemplos estão em [`requests.http`](./requests.http), prontos para a extensão REST Client do VS Code.

| Método | Rota | Descrição | Evento publicado |
|---|---|---|---|
| `POST` | `/mensagens` | Hello RabbitMQ: `{ "mensagem": "Olá RabbitMQ" }` | fila `mensagens.queue` |
| `POST` | `/pedidos` | Cria pedido (`cliente`, `produto`, `quantidade`, `valor`) | `pedido.criado` |
| `POST` | `/pedidos/{id}/pagamento` | Paga um pedido `CRIADO` | `pedido.pago` |
| `POST` | `/pedidos/{id}/cancelamento` | Cancela um pedido `CRIADO` | `pedido.cancelado` |
| `GET` | `/pedidos` | Lista pedidos | — |
| `GET` | `/pedidos/{id}` | Busca pedido por id | — |
| `POST` | `/testes/mensagem-invalida?routingKey=...` | Publica um payload qualquer, sem validação (demonstração da DLQ) | payload bruto |

**Respostas de erro:** `400` (dados inválidos), `404` (pedido inexistente), `409` (transição de status inválida, ex.: cancelar pedido já pago) e `503` (broker indisponível, sem vazar detalhes internos).

Exemplo de evento publicado:

```json
{
  "eventoId": "0b5e7f0c-2a61-4f1e-9d36-8c1f4f7f2a10",
  "tipo": "pedido.criado",
  "dataHora": "2026-09-30T17:15:11.135Z",
  "pedido": {
    "id": 1001,
    "cliente": "Maria",
    "produto": "Notebook",
    "quantidade": 2,
    "valor": 3500,
    "status": "CRIADO",
    "criadoEm": "2026-09-30T17:15:11.135Z"
  }
}
```

---

## 🛡️ Tratamento de mensagens inválidas

O consumidor **não confia no produtor**, porque qualquer serviço pode publicar na exchange. Toda mensagem passa por duas barreiras:

1. **Conversão:** JSON malformado gera `MessageConversionException`.
2. **Validação** (`PedidoEventoValidator`): campos obrigatórios, valores positivos e `tipo` igual à routing key recebida.

Em qualquer falha, a mensagem é rejeitada **sem requeue**. O RabbitMQ a encaminha para `pedidos.dlx` → `pedidos.dlq`, e o `DeadLetterConsumer` registra no log a fila de origem e o motivo, lidos do header `x-death`.

A DLQ usa um container próprio, sem conversão JSON e sem retry. Se o listener da DLQ também tentasse converter o payload, um JSON malformado falharia de novo e seria descartado, porque a DLQ não tem outra dead letter exchange.

```
[DLQ] Mensagem inválida vinda de 'financeiro.queue' (motivo: rejected): isso nao e json
```

---

## 📁 Estrutura do projeto

```
spring-distributed-systems/
├── docker-compose.yml          # RabbitMQ 4 + Management UI
├── pom.xml
├── requests.http               # Testes dos endpoints (REST Client)
└── src/
    ├── main/java/br/edu/rabbitmq/
    │   ├── config/
    │   │   ├── RabbitMQConfig.java            # Exchanges, filas, bindings, DLQ e conversor JSON
    │   │   ├── RabbitRetryConfig.java         # Retry só para falhas transitórias
    │   │   └── DeadLetterListenerConfig.java  # Container da DLQ (sem conversão/retry)
    │   ├── controller/         # PedidoController, MensagemController, TesteController
    │   ├── service/            # PedidoService: regras de status e publicação dos eventos
    │   ├── producer/           # PedidoProducer (TOPIC) e MensagemProducer (default exchange)
    │   ├── consumer/           # Estoque, Pagamento, Notificação, Mensagem, DeadLetter + validador
    │   ├── model/              # Pedido, PedidoEvento, StatusPedido
    │   ├── dto/                # PedidoRequest, MensagemRequest (Bean Validation)
    │   ├── repository/         # Armazenamento em memória
    │   └── exception/          # Exceções e handler global (400/404/409/503)
    ├── main/resources/application.properties
    └── test/java/.../PedidoEventoValidatorTest.java
```

---

## ✅ Requisitos atendidos

| Etapa / Requisito | Onde |
|---|---|
| Etapa 1: Producer, Queue e Consumer | `MensagemProducer`, `mensagens.queue`, `MensagemConsumer` |
| Etapa 2: `POST /mensagens` | `MensagemController` |
| Etapa 3: Pedido publicado como JSON | `Pedido`, `PedidoEvento`, `Jackson2JsonMessageConverter` |
| Etapa 4: Eventos e filas com TOPIC | `pedido.criado/pago/cancelado` → `estoque`, `financeiro`, `notificacao` |
| 1–2. Cadastro de pedido e publicação do evento | `POST /pedidos` → `pedido.criado` |
| 3–5. Consumidores de estoque, pagamento e notificação | pacote `consumer` |
| 6–8. Exchange TOPIC, routing keys, pelo menos três filas | `RabbitMQConfig` |
| 9. Monitoramento pelo RabbitMQ Management | http://localhost:15672 |
| 10. Tratamento de mensagens inválidas | `PedidoEventoValidator` + DLQ |

---

## 🎯 Objetivo

Aplicar os conceitos de sistemas distribuídos (processamento assíncrono, comunicação orientada a eventos, desacoplamento, escalabilidade e tolerância a falhas) em uma arquitetura que combina **REST** para a entrada síncrona e **mensageria** para o processamento assíncrono.
