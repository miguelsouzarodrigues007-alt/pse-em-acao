# PSE em Ação — Sistema de Planejamento e Acompanhamento de Ações de Saúde na Escola

AEP — 2º semestre de 2026  
Universidade Cesumar (UniCesumar)  
Curso: Engenharia de Software — Série: ESOFT2S

## Integrantes

| Nome                      | RA         |
| ------------------------- | ---------- |
| Miguel de Souza Rodrigues | 26000989-2 |
| Antonio Augusto Fuggi     | 26003652-2 |
| Rafael Lacava Rampazzo    | 26001885-2 |

## Proposta

Aplicação em linguagem C, executada em terminal, para apoiar o planejamento e o
acompanhamento de ações coletivas do Programa Saúde na Escola (PSE), instituído pelo
Decreto nº 6.286/2007.

A solução atende à equipe intersetorial fictícia IntegraPSE, que acompanha as ações
realizadas nas escolas de um município e hoje depende de anotações, formulários e
planilhas separadas.

**Tema escolhido para a demonstração:** Alimentação Saudável. O sistema, no entanto,
permite cadastrar ações de qualquer uma das 14 temáticas do PSE.

## Funcionalidades

1. Cadastrar ação (código, escola, tema, data prevista, público-alvo, responsável e quantidade prevista)
2. Listar todas as ações cadastradas
3. Pesquisar ações por código, por parte do nome da escola ou por tema
4. Atualizar a situação da ação (planejada, realizada ou cancelada) e registrar os participantes efetivos
5. Gerar resumo geral com totais por situação e percentual de participação
6. Gerar resumo por escola, destacando as escolas sem nenhuma ação realizada
7. Validar as entradas: códigos repetidos, quantidades negativas, campos vazios, datas inválidas,
   opções inexistentes e letras digitadas no lugar de números

## Como compilar e executar

O programa usa apenas bibliotecas padrão da linguagem C (`stdio.h`, `string.h` e `ctype.h`)
e funciona no Windows e no Linux.

**Com Code::Blocks ou Dev-C++ (Windows):** abra o arquivo `codigo/pse_em_acao.c` e use a
opção *Compilar e Executar*.

**Com GCC pelo terminal:**

```bash
cd codigo
gcc pse_em_acao.c -o pse
./pse        # Linux e macOS
pse.exe      # Windows
```

**No macOS:** se o terminal pedir para aceitar a licença do Xcode, aceite com
`sudo xcodebuild -license accept` ou compile direto pelas ferramentas de linha de comando:

```bash
DEVELOPER_DIR=/Library/Developer/CommandLineTools gcc pse_em_acao.c -o pse
```

## Estrutura do repositório

```
pse-em-acao/
├── README.md
├── codigo/
│   └── pse_em_acao.c          código-fonte do sistema
└── documentacao/
    ├── AEP_ESOFT2S_PSE_em_Acao_Etapa1_Miguel_Antonio_Rafael.pdf   documento da Etapa 1
    ├── AEP_ESOFT2S_PSE_em_Acao_Etapa2_Miguel_Antonio_Rafael.pdf   documento final da Etapa 2
    ├── diagrama_casos_de_uso.png
    └── capturas/               capturas de tela do programa em execução
```

## Limites éticos

O sistema opera exclusivamente com dados fictícios e informações coletivas sobre as ações.
Não armazena nome, diagnóstico, prontuário ou qualquer dado individual de estudante e não
realiza diagnóstico, triagem, prescrição ou recomendação de tratamento. No campo
"responsável" é informada a equipe ou a função, nunca o nome de uma pessoa.

## Etapas

- **Etapa 1 — Documento escrito:** produção textual, requisitos, fluxogramas,
  pseudocódigos e planejamento das sprints.
- **Etapa 2 — Implementação e apresentação:** código-fonte em C, casos de uso,
  requisitos atualizados, registro de testes, manual do usuário e vídeo.

**Vídeo de apresentação:** https://youtu.be/ClJCPshsZUM
