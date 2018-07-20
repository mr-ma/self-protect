#pragma once

#include "PDGNode.h"

#include "llvm/IR/Argument.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Value.h"

namespace pdg {

class PDGLLVMNode : public PDGNode
{
public:
    enum NodeType {
        InstructionNode,
        ArgumentNode,
        GlobalVariableNode,
        ConstantExprNode,
        ConstantNode,
        BasicBlockNode,
        UnknownNode
    };

    explicit PDGLLVMNode(llvm::Value* node_value)
        : m_value(node_value)
    {
    }

    virtual ~PDGLLVMNode() = default;

    llvm::Value* getNodeValue() const
    {
        return m_value;
    }

    virtual NodeType getNodeType() const
    {
        return NodeType::UnknownNode;
    }

private:
    llvm::Value* m_value;
}; // class PDGLLVMNode

class PDGLLVMInstructionNode : public PDGLLVMNode
{
public:
    explicit PDGLLVMInstructionNode(llvm::Instruction* instr)
        : PDGLLVMNode(instr)
    {
    }

    NodeType getNodeType() const override
    {
        return NodeType::InstructionNode;
    }
}; // class PDGInstructionNode

class PDGLLVMArgumentNode : public PDGLLVMNode
{
public:
    explicit PDGLLVMArgumentNode(llvm::Argument* arg)
        : PDGLLVMNode(arg)
    {
    }

    NodeType getNodeType() const override
    {
        return NodeType::ArgumentNode;
    }
}; // class PDGArgumentNode

class PDGLLVMGlobalVariableNode : public PDGLLVMNode
{
public:
    explicit PDGLLVMGlobalVariableNode(llvm::GlobalVariable* var)
        : PDGLLVMNode(var)
    {
    }

    NodeType getNodeType() const override
    {
        return NodeType::GlobalVariableNode;
    }

}; // class PDGGlobalVariableNodeNode

class PDGLLVMConstantExprNode : public PDGLLVMNode
{
public:
    explicit PDGLLVMConstantExprNode(llvm::ConstantExpr* expr)
        : PDGLLVMNode(expr)
    {
    }

    NodeType getNodeType() const override
    {
        return NodeType::ConstantExprNode;
    }

}; // class PDGConstantExprNode

class PDGLLVMConstantNode : public PDGLLVMNode
{
public:
    explicit PDGLLVMConstantNode(llvm::Constant* constant)
        : PDGLLVMNode(constant)
    {
    }

    NodeType getNodeType() const override
    {
        return NodeType::ConstantNode;
    }

}; // class PDGConstantNode

class PDGLLVMBasicBlockNode : public PDGLLVMNode
{
public:
    explicit PDGLLVMBasicBlockNode(llvm::BasicBlock* block)
        : PDGLLVMNode(llvm::dyn_cast<llvm::Value>(block))
    {
    }

    NodeType getNodeType() const override
    {
        return NodeType::BasicBlockNode;
    }

    virtual bool addInDataEdge(PDGEdgeType inEdge) override
    {
        assert(false);
    }

    virtual bool addOutDataEdge(PDGEdgeType outEdge) override
    {
        assert(false);
    }
}; // class PDGLLVMBasicBlockNode


} // namespace pdg

